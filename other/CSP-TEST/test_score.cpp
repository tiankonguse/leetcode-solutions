/**
 * CSP-J/S 考试评分系统
 * v1: 2025-11-12 基本版本，评测 N 个省份数据
 * v2: 2025-11-13 修复部分考生没有创建题目目录时报错的问题
 * v3: 2025-11-14 增加编译命令: c++ -std=c++2a -O2 test_score.cpp -o test_score
 * v4: 2025-11-14 删除测试的临时文件，避免磁盘空间占用过多
 * v5: 2025-11-14 新增调试信息开关 debugFlag，默认关闭
 * V6: 2025-11-14 参数解析改进，增加 --from 和 --to 参数，支持部分考生测试
 * V7: 2025-11-15 优化批量模式，指定批次和索引
 * V8: 2025-11-15 部分考生输出时没有写到文件，把输出重定向到 /dev/null，避免刷屏
 * V9: 2025-11-15 增加 --timeout 参数，支持设置程序运行超时时间，单位秒，范围 1-60
 * V10: 2025-11-15 修复部分考试代码运行失败时，没有清理输入输出文件的问题
 * V11: 2025-11-15 部分考生使用 cerr 输出调试信息，强制重定向到 /dev/null，避免刷屏
 * V12: 2025-11-17 支持配置每道题的内存和超时时间，以及配置时间放大系数
 *
 * cp /Users/tiankonguse-m3/project/github/leetcode-solutions/other/CSP-TEST/test_score.cpp ./
 * c++ -std=c++2a -O2 test_score.cpp -o test_score
 * -I/Users/tiankonguse-m3/project/github/leetcode-solutions/include/ -DUSACO_LOCAL_JUDGE
 */

#include <bits/stdc++.h>
#include <spawn.h>
#include <unistd.h>     // For environ
extern char** environ;  // Declare environ explicitly
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

#ifdef USACO_LOCAL_JUDGE
// MAC 电脑没有 bits/stdc++.h， 所以指定自己写的 bits/stdc++.h 路径
#define PRJ_ROOT_PATH "/Users/tiankonguse-m3/project/github/leetcode-solutions/"
#define BITS_STDC " -I" PRJ_ROOT_PATH "include/ "
#else
#define BITS_STDC " "
#define CODE_PATH ""
#endif

// 输入: 考生代码路径, 官方数据路径
// 目标： 统计考生代码在官方数据下的得分情况
// 分数计算方式：每道题 100 分，每道题 X 组测试数据（保证可以被100整除），每组测试数据通过得分 100/X 分。
/*
  考生代码路径, 目录格式参考文章 https://mp.weixin.qq.com/s/2CJBXOxT5lXoN_jNqDhaKQ
  code/
    XX-S000001/
      arena/
          arena.cpp
      color/
          color.cpp
      detect/
          detect.cpp
      employ/
          employ.cpp
    XX-S000002/
      ...

  官方数据路径
  data/
    arena1.in
    arena1.ans
    arena2.in
    arena2.ans
    ...
    color1.in
    color1.ans
    ...
    detect1.in
    detect1.ans
    ...
    employ1.in
    employ1.ans
    ...
*/

// 简单固定大小线程池（C++14）

struct Node {
  string problem_name;
  int sample_count;
  double timeout;
  int memory;
};
map<string, Node> problem_samples;

string main_path;
string official_data_path;
// 探测系统上 timeout 或 gtimeout 命令（macOS 上用 gtimeout 来自 coreutils）
string timeout_cmd = "gtimeout";
int ioFlag = 1;              // 0 代表程序里不从文件读写， 1 代表程序里从文件读写
int batchNum = 1;            // 1 批就是全量运行
int batchIndex = 0;          // 0 代表运行  % batchNum = 0 的学生， 1 代表运行 % batchNum = 1 的学生， 以此类推
int debugFlag = 0;           // 0 代表不打印调试信息， 1 代表打印调试信息
int lastNum = -1;            // 默认不分组，全量运行
int fromNum = 1;             // 默认从第 1 个学生开始跑
int toNum = 1000000;         // 默认跑到最后一个学生
double timeout_scale = 1.0;  // 程序运行超时时间放大系数，默认 1.0

#define MyPrintf(...)                   \
  do {                                  \
    if (debugFlag) printf(__VA_ARGS__); \
  } while (0)

// mac 电脑 system 不支持并发，所以只能顺序执行
int run_compile(const char* cmd) {
  return system(cmd);  //
}

int TestOneProblem(const string& problem_dir) {
  // 已经 cd 到问题目录了，所以这里面全是文件，不需要加路径前缀
  const string problem_name = filesystem::path(problem_dir).filename().string();
  assert(problem_samples.find(problem_name) != problem_samples.end());
  Node& node = problem_samples[problem_name];
  int sample_count = node.sample_count;
  double timeout = node.timeout;
  int memory = node.memory * 1024;
  MyPrintf("Testing problem %s with %d samples, timeout %f, memory %d\n", problem_name.c_str(), sample_count, timeout,
           memory);

  // 只有一个代码，文件名与目录名一致
  string code_path = "./" + problem_name + ".cpp";
  if (!filesystem::exists(code_path)) {
    MyPrintf("Code file %s does not exist for problem %s\n", code_path.c_str(), problem_name.c_str());
    return 0;  // 没传代码，0 分
  }

  string exe_path = "./" + problem_name + ".exe";
  string compile_cmd = "g++ " + code_path + " -O2 -std=c++14  " + BITS_STDC;
  compile_cmd += " -Wno-c++11-narrowing ";
  compile_cmd += " -Werror=return-type ";
  compile_cmd += " -o " + exe_path;
  if (debugFlag == 0) {
    compile_cmd += "  2>/dev/null";
  }
  MyPrintf("Compiling problem %s with command: %s\n", problem_name.c_str(), compile_cmd.c_str());
  if (run_compile(compile_cmd.c_str()) != 0) {
    MyPrintf("Compilation failed for problem %s\n", compile_cmd.c_str());
    return 0;  // 编译失败，得分 0
  }
  // 检查编译文件是否存在
  if (!filesystem::exists(exe_path)) {
    MyPrintf("Executable file %s does not exist after compilation for problem %s\n", exe_path.c_str(),
             problem_name.c_str());
    return 0;  // 编译失败，得分 0
  }

  // 遍历官方数据，逐个测试
  int passed_tests = 0;
  // 检查系统上是否有 timeout 或 gtimeout（macOS 上用 gtimeout 来自 coreutils）
  for (int i = 1; i <= sample_count; i++) {
    const string official_input_file_path_i = official_data_path + "/" + problem_name + to_string(i) + ".in";
    const string official_answer_file_path_i = official_data_path + "/" + problem_name + to_string(i) + ".ans";
    const string student_output_file_path_i = "./" + problem_name + to_string(i) + ".out";
    const string student_output_file_path = "./" + problem_name + ".out";
    const string student_input_file_path = "./" + problem_name + ".in";

    // output_file_path_i 文件清空
    run_compile(("echo > " + student_output_file_path_i).c_str());
    run_compile(("echo > " + student_output_file_path).c_str());

    // input_file_path_i 是官方数据的输入文件，拷贝到考生目录下作为输入文件
    filesystem::copy_file(official_input_file_path_i, student_input_file_path,
                          filesystem::copy_options::overwrite_existing);

    string ulimit = "ulimit -m " + to_string(memory);
    string run_cmd = ulimit + " && " + timeout_cmd + " " + to_string(timeout) + " " + exe_path;
    if (ioFlag == 0) {
      run_cmd += " < " + student_input_file_path;
      run_cmd += " > " + student_output_file_path;
    } else {
      run_cmd += " > /dev/null";  // 把程序输出重定向到 /dev/null，避免刷屏
    }
    // 为了防止部分考生使用 cerr 输出调试信息，强制重定向到 /dev/null
    run_cmd += " 2> /dev/null";
    MyPrintf("Running problem %s with command: %s\n", problem_name.c_str(), run_cmd.c_str());
    int ret = run_compile(run_cmd.c_str());
    if (ret != 0) {
      MyPrintf("Runtime error or timeout on test %d for problem %s\n", i + 1, problem_name.c_str());
      continue;  // 运行错误，跳过该测试点
    }

    if (!filesystem::exists(student_output_file_path)) {
      MyPrintf("Output file %s does not exist after running test %d for problem %s\n", student_output_file_path.c_str(),
               i + 1, problem_name.c_str());
      continue;  // 某种原因输出文件不见了，跳过该测试点
    }
    filesystem::copy_file(student_output_file_path, student_output_file_path_i,
                          filesystem::copy_options::overwrite_existing);

    // 比较输出结果
    string diff_cmd = "diff -w " + official_answer_file_path_i + " " + student_output_file_path_i + " > /dev/null";
    if (run_compile(diff_cmd.c_str()) == 0) {
      MyPrintf("    Test %d passed for problem %s\n", i, problem_name.c_str());
      passed_tests++;
    } else {
      MyPrintf("    Test %d failed for problem %s\n", i, problem_name.c_str());
    }
  }

  // 清理最后的输入输出文件
  const string student_output_file_path = "./" + problem_name + ".out";
  const string student_input_file_path = "./" + problem_name + ".in";
  if (filesystem::exists(student_input_file_path)) {
    filesystem::remove(student_input_file_path);
  }
  if (filesystem::exists(student_output_file_path)) {
    filesystem::remove(student_output_file_path);
  }
  for (int i = 1; i <= sample_count; i++) {
    const string student_output_file_path_i = "./" + problem_name + to_string(i) + ".out";
    // 先检查是否存在再删除
    if (filesystem::exists(student_output_file_path_i)) {
      filesystem::remove(student_output_file_path_i);
    }
  }
  // 删除可执行文件
  filesystem::remove(exe_path);
  return (passed_tests * 100) / sample_count;
};

tuple<int, int, int, int> TestOneStudent(const string& student_dir) {
  printf("Testing student: %s\n", student_dir.c_str());
  string student_id = filesystem::path(student_dir).filename().string();
  auto t1 = std::chrono::steady_clock::now();
  vector<pair<string, int>> problem_scores;
  for (auto [problem_name, sample_count] : problem_samples) {
    const string problem_dir = student_dir + "/" + problem_name;

    // 判断目录是否存在
    if (!filesystem::exists(problem_dir) || !filesystem::is_directory(problem_dir)) {
      printf("  Problem directory %s does not exist for student %s\n", problem_dir.c_str(), student_id.c_str());
      problem_scores.push_back({problem_name, 0});
      continue;
    }

    filesystem::current_path(problem_dir);  // cd 到问题目录
    int problem_score = TestOneProblem(problem_dir);
    filesystem::current_path(main_path);  // 切回主路径
    problem_scores.push_back({problem_name, problem_score});
  }
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  double costTime = my.count();

  int all_score =
      (problem_scores[0].second + problem_scores[1].second + problem_scores[2].second + problem_scores[3].second);
  printf("  Student %s allScore=%d, problem score: %s=%d %s=%d %s=%d %s=%d, costTime=%.2f ms\n", student_id.c_str(),
         all_score, problem_scores[0].first.c_str(), problem_scores[0].second, problem_scores[1].first.c_str(),
         problem_scores[1].second, problem_scores[2].first.c_str(), problem_scores[2].second,
         problem_scores[3].first.c_str(), problem_scores[3].second, costTime);
  return {problem_scores[0].second, problem_scores[1].second, problem_scores[2].second, problem_scores[3].second};
}

bool Init(string user_code_path) {
  // 先探测 timeout 或 gtimeout 命令, 优先使用 timeout, 如果没有再使用 gtimeout
  if (run_compile("timeout --version > /dev/null 2>&1") == 0) {
    timeout_cmd = "timeout";
    printf("Using timeout command for time limit enforcement.\n");
  } else if (run_compile("gtimeout --version > /dev/null 2>&1") == 0) {
    timeout_cmd = "gtimeout";
    printf("Using gtimeout command for time limit enforcement.\n");
  } else {
    printf("Error: Neither timeout nor gtimeout command found. Please install coreutils\n");
    return false;
  }

  // 检查 user_code_path 和 official_data_path 是否存在
  if (!filesystem::exists(user_code_path)) {
    printf("Error: User code path %s does not exist.\n", user_code_path.c_str());
    return false;
  }
  if (!filesystem::exists(official_data_path)) {
    printf("Error: Official data path %s does not exist.\n", official_data_path.c_str());
    return false;
  }

  // 遍历 official_data_path 目录，统计每道题有几个样例
  map<string, set<int>> problem_sample_set;
  for (const auto& entry : filesystem::directory_iterator(official_data_path)) {
    if (entry.is_regular_file()) {
      string filename = entry.path().filename().string();
      // 文件名格式: problemNameXX.in 或 problemNameXX.ans
      size_t pos = filename.find_first_of("0123456789");
      size_t dot = filename.find_first_of(".");
      if (pos != string::npos) {
        string problem_name = filename.substr(0, pos);           // name
        int problem_no = stoi(filename.substr(pos, dot - pos));  // XX
        problem_sample_set[problem_name].insert(problem_no);
      }
    }
  }
  // 统计每道题的样例数量
  // 检查数据完整性， 预期 problem_no 从 1 到 sample_count 连续
  for (const auto& [problem_name, sample_set] : problem_sample_set) {
    int sample_count = sample_set.size();
    for (int i = 1; i <= sample_count; i++) {
      if (sample_set.find(i) == sample_set.end()) {
        printf("Warning: Missing Data %d for problem %s\n", i, problem_name.c_str());
        return false;
      }
    }
  }
  problem_samples.clear();
  for (const auto& [problem_name, sample_set] : problem_sample_set) {
    Node& node = problem_samples[problem_name];
    node.problem_name = problem_name;
    node.sample_count = sample_set.size();
  }

  // 加载 perblem.txt 数据
  string problem_txt_path = main_path + "/perblem.txt";
  if (!filesystem::exists(problem_txt_path)) {
    printf("Error: Problem txt path %s does not exist.\n", problem_txt_path.c_str());
    return false;
  }
  {
    freopen(problem_txt_path.c_str(), "r", stdin);
    Node tmpNode;
    char tmpProblemName[100];
    while (scanf("%s %lf %d %d", tmpProblemName, &tmpNode.timeout, &tmpNode.memory, &tmpNode.sample_count) != EOF) {
      tmpNode.problem_name = tmpProblemName;
      if (problem_samples.count(tmpNode.problem_name) == 0) {
        printf("Error: Problem %s not found in problem data\n", tmpNode.problem_name.c_str());
        return false;
      }
      Node& node = problem_samples[tmpNode.problem_name];
      if (node.sample_count != tmpNode.sample_count) {
        printf("Error: Problem %s sample count not match, problem.txt Count is %d, data Count is %d\n",
               tmpNode.problem_name.c_str(), tmpNode.sample_count, node.sample_count);
        return false;
      }
      node.problem_name = tmpNode.problem_name;
      node.timeout = tmpNode.timeout * timeout_scale;
      node.memory = tmpNode.memory;
    }
  }

  printf("Detected problems and sample counts:\n");
  for (const auto& [problem_name, node] : problem_samples) {
    printf("  Problem %s has %d samples, timeout=%.1f memory=%dM\n", problem_name.c_str(), node.sample_count,
           node.timeout, node.memory);
  }

  return true;
}

void Usage() {
  printf("\n");
  printf("Usage:\n");
  printf("    --batch=N  批次，指定批次号，默认 1 全量运行\n");
  printf("    --index=M  索引，指定批次内的索引号\n");
  printf("    --IO=ioFlag , 默认值 1，程序里是否从文件读测试数据， 1 代表是， 0 代表否\n");
  printf("    --debug=debugFlag , 默认值 0，是否打印调试信息， 1 代表打印， 0 代表不打印\n");
  printf("    --from=num , 默认值 1， 从 num 开始跑数据\n");
  printf("    --to=num , 默认值 max， 到 num 结束跑数据\n");
  printf("    --scale=t , 默认值 1.0， 程序运行超时时间放大系数，范围 1.0~3.0\n");
  printf("\n");
  printf("学生的代码放在 code 目录，子目录为学生考试编号\n");
  printf("官方测试数据放在 data 目录，是测试数据文件列表\n");
  printf("Linux 使用 timeout 命令来限制程序运行时间;Mac 使用 gtimeout 命令，需要安装依赖 brew install coreutils\n");
  printf(
      "perblem.txt 每道题一行，四列空格分隔，分别为 "
      "目录名、时间限制(单位秒，支持浮点数)、内存限制(单位M)、测试点数目\n");
  printf("例如： \n");
  printf("club 1.0 512 20\n");
  printf("road 1.0 512 25\n");
  printf("replace 1.0 2048 20\n");
  printf("employ 1.0 512 25\n");
  printf("\n");
  printf("目录结构如下\n");
  printf("test_score.cpp\n");
  printf("perblem.txt\n");
  printf("code/\n");
  printf("    XX-S000001/\n");
  printf("        arena/\n");
  printf("            arena.cpp\n");
  printf("        color/\n");
  printf("            color.cpp\n");
  printf("        detect/\n");
  printf("            detect.cpp\n");
  printf("        employ/\n");
  printf("            employ.cpp\n");
  printf("    XX-S000002/\n");
  printf("        ...\n");
  printf("\n");
  printf("data/\n");
  printf("    arena1.in\n");
  printf("    arena1.ans\n");
  printf("    arena2.in\n");
  printf("    arena2.ans\n");
  printf("    ...\n");
  printf("    color1.in\n");
  printf("    color1.ans\n");
  printf("    ...\n");
  printf("    detect1.in\n");
  printf("    detect1.ans\n");
  printf("    ...\n");
  printf("    employ1.in\n");
  printf("    employ1.ans\n");
  printf("    ...\n");
}

// 判断字符串是否以 prefix 开头
bool starts_with(const std::string& s, const std::string& prefix) { return s.rfind(prefix, 0) == 0; }
bool ParseArgs(int argc, char** argv) {
  const string kBatchPrefix = "--batch=";
  const string kIndexPrefix = "--index=";
  const string kIOPrefix = "--IO=";
  const string kDebugPrefix = "--debug=";
  const string kFromPrefix = "--from=";
  const string kToPrefix = "--to=";
  const string kScalePrefix = "--scale=";
  std::vector<std::string> args(argv + 1, argv + argc);
  for (size_t i = 0; i < args.size(); i++) {
    const std::string& arg = args[i];
    if (starts_with(arg, kBatchPrefix)) {
      batchNum = std::stoi(arg.substr(kBatchPrefix.size()));
      if (batchNum < 1) {
        printf("Error: batchNum (%d) must be greater than 0\n", batchNum);
        return false;
      }
    } else if (starts_with(arg, kIndexPrefix)) {
      batchIndex = std::stoi(arg.substr(kIndexPrefix.size()));
      if (batchIndex < 0 || batchIndex >= batchNum) {
        printf("Error: batchIndex (%d) must be in [0, %d)\n", batchIndex, batchNum);
        return false;
      }
    } else if (starts_with(arg, kIOPrefix)) {
      ioFlag = std::stoi(arg.substr(kIOPrefix.size()));
      if (ioFlag < 0 || ioFlag > 1) {
        printf("Error: ioFlag (%d) must be 0 or 1\n", ioFlag);
        return false;
      }
    } else if (starts_with(arg, kDebugPrefix)) {
      debugFlag = std::stoi(arg.substr(kDebugPrefix.size()));
      if (debugFlag < 0 || debugFlag > 1) {
        printf("Error: debugFlag (%d) must be 0 or 1\n", debugFlag);
        return false;
      }
    } else if (starts_with(arg, kFromPrefix)) {
      fromNum = std::stoi(arg.substr(kFromPrefix.size()));
      if (fromNum < 1) {
        printf("Error: fromNum (%d) must be greater than 0\n", fromNum);
        return false;
      }
    } else if (starts_with(arg, kToPrefix)) {
      toNum = std::stoi(arg.substr(kToPrefix.size()));
      if (toNum < fromNum) {
        printf("Error: toNum (%d) must be greater than or equal to fromNum (%d)\n", toNum, fromNum);
        return false;
      }
    } else if (starts_with(arg, kScalePrefix)) {
      timeout_scale = std::stof(arg.substr(kScalePrefix.size()));
      if (timeout_scale < 1.0 || timeout_scale > 3.0) {
        printf("Error: timeout_scale (%.1f) must be in [1.0, 3.0]\n", timeout_scale);
        return false;
      }
    } else {
      printf("Unknown argument: %s\n", arg.c_str());
      return false;
    }
  }
  if (batchIndex >= batchNum) {
    printf("Error: batchIndex (%d) must be less than batchNum (%d)\n", batchIndex, batchNum);
    return false;
  }
  if (batchNum == 1) {
    printf("Running all students from %d to %d\n", fromNum, toNum);
  } else {
    printf("Running batch=%d only students with last number %d, from %d to %d\n", batchNum, batchIndex, fromNum, toNum);
  }
  if (ioFlag) {
    printf("IO Flag is ON: Programs will read/write from/to files.\n");
  } else {
    printf("IO Flag is OFF: Programs will use standard input/output.\n");
  }
  if (debugFlag) {
    printf("Debug Flag is ON: Debug information will be printed.\n");
  } else {
    printf("Debug Flag is OFF: No debug information will be printed.\n");
  }
  printf("Timeout scale is %.1f\n", timeout_scale);

  return true;
}

int main(int argc, char** argv) {
  if (ParseArgs(argc, argv) == false) {
    Usage();
    return 0;
  }

  main_path = filesystem::current_path().string();  // 获取当前程序的路径
  string out_result_path = batchNum == 1 ? "./results.txt" : "./results" + to_string(batchIndex) + ".txt";
  out_result_path = main_path + "/" + out_result_path;
  string user_code_path = main_path + "/code";
  official_data_path = main_path + "/data";
  printf("Main path: %s\n", main_path.c_str());
  printf("Code path: %s\n", user_code_path.c_str());
  printf("Data path: %s\n", official_data_path.c_str());

  if (!Init(user_code_path)) {
    Usage();
    return 0;
  }

  // 遍历考生目录
  vector<std::string> student_dirs;
  for (const auto& entry : filesystem::directory_iterator(user_code_path)) {
    if (entry.is_directory()) {
      string student_dir = entry.path().string();
      // 文件名格式 XX-S000001， 考试编号是后五位数字
      string student_id = filesystem::path(student_dir).filename().string();
      if (student_id.length() < 7) {
        printf("Skipping invalid student_dir: %s\n", entry.path().string().c_str());
        continue;
      }
      int student_num = stoi(student_id.substr(student_id.length() - 5, 5));
      if (student_num < fromNum || student_num > toNum) {
        // printf("Skipping student_dir out of range: %s\n", entry.path().string().c_str());
        continue;
      }
      if (student_num % batchNum != batchIndex) {
        // printf("Skipping student_dir not in batch %d index %d: %s\n", batchNum, batchIndex,
        // entry.path().string().c_str());
        continue;
      }
      student_dirs.push_back(student_dir);
    } else {
      printf("Skipping non-directory student_dir: %s\n", entry.path().string().c_str());
    }
  }
  sort(student_dirs.begin(), student_dirs.end());  // 按顺序一个个测试
  printf("Total %zu students found in %s\n", student_dirs.size(), user_code_path.c_str());

  map<string, tuple<int, int, int, int>> student_scores;  // 使用 map 储存，方便后续按学生 ID 顺序输出结果
  for (auto& student_dir : student_dirs) {
    string student_id = filesystem::path(student_dir).filename().string();
    student_scores[student_id] = TestOneStudent(student_dir);
  }
  vector<string> problem_ids;
  for (auto& [problem_id, _] : problem_samples) {
    problem_ids.push_back(problem_id);
  }

  run_compile(("echo > " + out_result_path).c_str());
  // 下面的打印改为输出到文件
  freopen(out_result_path.c_str(), "a", stdout);
  printf("%10s %10s %10s %10s %10s %10s\n", "StudentID", "AllScore", problem_ids[0].c_str(), problem_ids[1].c_str(),
         problem_ids[2].c_str(), problem_ids[3].c_str());
  for (auto& [student_id, scores] : student_scores) {
    int all_score = (get<0>(scores) + get<1>(scores) + get<2>(scores) + get<3>(scores));
    printf("%10s %10d %10d %10d %10d %10d\n", student_id.c_str(), all_score, get<0>(scores), get<1>(scores),
           get<2>(scores), get<3>(scores));
  }
  return 0;
}