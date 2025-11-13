/**
 * CSP-J/S 考试评分系统
 * v1: 2025-11-12 基本版本，评测 N 个省份数据
 * v2: 2025-11-13 修复部分考生没有创建题目目录时报错的问题 
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

map<string, int> problem_samples;

string main_path;
string official_data_path;
// 探测系统上 timeout 或 gtimeout 命令（macOS 上用 gtimeout 来自 coreutils）
string timeout_cmd = "gtimeout";
int ioFlag;

// mac 电脑 system 不支持并发，所以只能顺序执行
int run_compile(const char* cmd) {
  return system(cmd);  //
}

int TestOneProblem(const string& problem_dir) {
  // 已经 cd 到问题目录了，所以这里面全是文件，不需要加路径前缀
  const string problem_name = filesystem::path(problem_dir).filename().string();
  assert(problem_samples.find(problem_name) != problem_samples.end());
  int sample_count = problem_samples[problem_name];

  // 只有一个代码，文件名与目录名一致
  string code_path = "./" + problem_name + ".cpp";
  if (!filesystem::exists(code_path)) {
    // printf("Code file %s does not exist for problem %s\n", code_path.c_str(), problem_name.c_str());
    return 0;  // 没传代码，0 分
  }

  string exe_path = "./" + problem_name + ".exe";
  string compile_cmd = "g++ " + code_path + " -O2 -std=c++14  " + BITS_STDC + " -o " + exe_path + " 2>/dev/null";
  if (run_compile(compile_cmd.c_str()) != 0) {
    // printf("Compilation failed for problem %s\n", compile_cmd.c_str());
    return 0;  // 编译失败，得分 0
  }
  // 检查编译文件是否存在
  if (!filesystem::exists(exe_path)) {
    // printf("Executable file %s does not exist after compilation for problem %s\n", exe_path.c_str(),
    //        problem_name.c_str());
    return 0;  // 编译失败，得分 0
  }

  // 遍历官方数据，逐个测试
  int passed_tests = 0;
  // 检查系统上是否有 timeout 或 gtimeout（macOS 上用 gtimeout 来自 coreutils）
  for (int i = 1; i <= sample_count; i++) {
    const string input_file_path_i = official_data_path + "/" + problem_name + to_string(i) + ".in";
    const string answer_file_path_i = official_data_path + "/" + problem_name + to_string(i) + ".ans";
    const string output_file_path_i = "./" + problem_name + to_string(i) + ".out";
    const string output_file_path = "./" + problem_name + ".out";
    const string input_file_path = "./" + problem_name + ".in";

    // output_file_path_i 文件清空
    run_compile(("echo > " + output_file_path_i).c_str());
    run_compile(("echo > " + output_file_path).c_str());

    // input_file_path_i 是官方数据的输入文件，拷贝到考生目录下作为输入文件
    filesystem::copy_file(input_file_path_i, input_file_path, filesystem::copy_options::overwrite_existing);

    string run_cmd = timeout_cmd + " 1 " + exe_path;
    if (ioFlag == 0) {
      run_cmd += " < " + input_file_path;
      run_cmd += " > " + output_file_path;
    }
    int ret = run_compile(run_cmd.c_str());
    if (ret != 0) {
      // printf("Runtime error or timeout on test %d for problem %s\n", i + 1, problem_name.c_str());
      continue;  // 运行错误，跳过该测试点
    }

    if (!filesystem::exists(output_file_path)) {
      printf("Output file %s does not exist after running test %d for problem %s\n", output_file_path.c_str(), i + 1,
             problem_name.c_str());
      continue;  // 某种原因输出文件不见了，跳过该测试点
    }
    filesystem::copy_file(output_file_path, output_file_path_i, filesystem::copy_options::overwrite_existing);

    // 比较输出结果
    string diff_cmd = "diff -w " + answer_file_path_i + " " + output_file_path_i + " > /dev/null";
    if (run_compile(diff_cmd.c_str()) == 0) {
      // printf("    Test %d passed for problem %s\n", i + 1, problem_name.c_str());
      passed_tests++;
    } else {
      // printf("    Test %d failed for problem %s\n", i + 1, problem_name.c_str());
    }
  }
  return (passed_tests * 100) / sample_count;
};

tuple<int, int, int, int> TestOneStudent(const string& student_dir) {
  printf("Testing student: %s\n", student_dir.c_str());
  string student_id = filesystem::path(student_dir).filename().string();

  vector<int> problem_scores;
  for (auto [problem_name, sample_count] : problem_samples) {
    const string problem_dir = student_dir + "/" + problem_name;

    // 判断目录是否存在
    if (!filesystem::exists(problem_dir) || !filesystem::is_directory(problem_dir)) {
      printf("  Problem directory %s does not exist for student %s\n", problem_dir.c_str(), student_id.c_str());
      problem_scores.push_back(0);
      continue;
    }

    filesystem::current_path(problem_dir);  // cd 到问题目录
    int problem_score = TestOneProblem(problem_dir);
    filesystem::current_path(main_path);  // 切回主路径
    problem_scores.push_back(problem_score);
  }

  int all_score = (problem_scores[0] + problem_scores[1] + problem_scores[2] + problem_scores[3]);
  printf("  Student %s allScore=%d, problem score: %d %d %d %d\n", student_id.c_str(), all_score, problem_scores[0],
         problem_scores[1], problem_scores[2], problem_scores[3]);
  return {problem_scores[0], problem_scores[1], problem_scores[2], problem_scores[3]};
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
    problem_samples[problem_name] = sample_set.size();
  }
  printf("Detected problems and sample counts:\n");
  for (const auto& [problem_name, sample_count] : problem_samples) {
    printf("  Problem %s has %d samples\n", problem_name.c_str(), sample_count);
  }
  return true;
}

void Usage() {
  printf("\n");
  printf("Usage: ./run_score lastNum ioFlag\n");
  printf("\n");
  printf("lastNum: 并发度，范围为 [0,9]，代表考试编号最后一位。 -1 代表不分组，串行运行\n");
  printf("ioFlag: 程序里是否从文件读测试数据， 1 代表是， 0 代表否\n");
  printf("\n");
  printf("学生的代码放在 code 目录，子目录为学生考试编号\n");
  printf("官方测试数据放在 data 目录，是测试数据文件列表\n");
  printf("Linux 使用 timeout 命令来限制程序运行时间;Mac 使用 gtimeout 命令，需要安装依赖 brew install coreutils\n");
  printf("\n");
  printf("目录结构如下\n");
  printf("test_score.cpp\n");
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

int main(int argc, char** argv) {
  if (argc != 3) {
    Usage();
    return 0;
  }

  const int lastNum = atoi(argv[1]);
  ioFlag = atoi(argv[2]);
  if (lastNum < -1 || lastNum > 9 || ioFlag < 0 || ioFlag > 1) {
    Usage();
    return 0;
  }
  string out_result_path = lastNum == -1 ? "./results.txt" : "./results" + to_string(lastNum) + ".txt";
  main_path = filesystem::current_path().string();  // 获取当前程序的路径
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
    int last_student_num = student_id.back() - '0';
    if (lastNum == -1) {
      student_scores[student_id] = TestOneStudent(student_dir);
      continue;
    }
    if (last_student_num == lastNum) {
      student_scores[student_id] = TestOneStudent(student_dir);
    }
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