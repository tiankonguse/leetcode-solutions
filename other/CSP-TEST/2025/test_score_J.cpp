#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

#define PRJ_ROOT_PATH "../../"

#ifdef USACO_LOCAL_JUDGE
#define BITS_STDC " -I" PRJ_ROOT_PATH "include/ "
#else
#define BITS_STDC " "
#define CODE_PATH ""
#endif

// 输入: 考生代码路径, 官方数据路径
// 目标： 统计考生代码在官方数据下的得分情况
// 分数计算方式：每道题 100 分，每道题 X 组测试数据（保证可以被100整除），每组测试数据通过得分 100/X 分。
/*
  user_code_path: 考生代码路径
  目录格式：
  user_code_path/
    CQ-S000001/
      arena/
          arena.cpp
      color/
          color.cpp
      detect/
          detect.cpp
      employ/
          employ.cpp
    CQ-S000002/
      ...

  official_data_path: 官方数据路径
  official_data_path/
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

map<string, int> problem_samples;

string main_path;
int TestOneProblem(const string& problem_dir, const string& official_data_path) {
  // printf("    Testing problem directory: %s\n", problem_dir.c_str());
  // 获取目录名， 例如 problem_dir = ".../CQ-S000001/arena", 则 problem_name = "arena"
  string problem_name = filesystem::path(problem_dir).filename().string();
  assert(problem_samples.find(problem_name) != problem_samples.end());
  int sample_count = problem_samples[problem_name];
  // printf("Problem %s has %d samples\n", problem_name.c_str(), sample_count);

  // 只有一个代码，文件名与目录名一致
  // 拼出目录名下的代码文件路径，例如 ".../CQ-S000001/arena/arena.cpp"
  string code_file_path = problem_dir + "/" + problem_name + ".cpp";
  // 检查代码文件是否存在
  if (!filesystem::exists(code_file_path)) {
    // printf("Code file %s does not exist for problem %s\n", code_file_path.c_str(), problem_name.c_str());
    return 0;
  }
  // 编译代码
  string exe_file_path = problem_dir + "/" + problem_name + ".exe";
  string compile_cmd = "g++ " + code_file_path + " -O2 -std=c++14  " + BITS_STDC + " -o " + exe_file_path + " -O2";
  if (system(compile_cmd.c_str()) != 0) {
    printf("Compilation failed for problem %s\n", problem_name.c_str());
    // 编译失败，得分 0
    return 0;
  }
  // 检查编译文件是否存在
  if (!filesystem::exists(exe_file_path)) {
    printf("Executable file %s does not exist after compilation for problem %s\n", exe_file_path.c_str(),
           problem_name.c_str());
    return 0;
  }
  // 遍历官方数据，逐个测试
  int passed_tests = 0;
  // 检查系统上是否有 timeout 或 gtimeout（macOS 上用 gtimeout 来自 coreutils）
  for (int i = 0; i < sample_count; i++) {
    string input_file_path = official_data_path + "/" + problem_name + to_string(i + 1) + ".in";
    string answer_file_path = official_data_path + "/" + problem_name + to_string(i + 1) + ".ans";
    string output_file_path = problem_dir + "/" + problem_name + to_string(i + 1) + ".out";
    // 先清空 student.out，避免旧数据影响
    system(("echo > " + output_file_path).c_str());
    // 运行考生代码（优先使用 timeout/gtimeout，如果都不存在则不设置超时）
    string run_cmd = "gtimeout 1 " + exe_file_path + " < " + input_file_path + " > " + output_file_path;
    int ret = system(run_cmd.c_str());
    if (ret != 0) {
      // printf("Runtime error or timeout on test %d for problem %s\n", i + 1, problem_name.c_str());
      // 运行错误，跳过该测试点
      continue;
    }
    // 检查输出文件是否存在
    if (!filesystem::exists(output_file_path)) {
      // printf("Output file %s does not exist after running for test %d for problem %s\n", output_file_path.c_str(), i + 1,
      //        problem_name.c_str());
      continue;
    }
    // 比较输出结果
    string diff_cmd = "diff -w " + answer_file_path + " " + output_file_path + " > /dev/null";
    if (system(diff_cmd.c_str()) == 0) {
      // printf("    Test %d passed for problem %s\n", i + 1, problem_name.c_str());
      // 通过该测试点
      passed_tests++;
    } else {
      // printf("    Test %d failed for problem %s\n", i + 1, problem_name.c_str());
    }
  }
  return (passed_tests * 100) / sample_count;
};

tuple<int, int, int, int> TestOneStudent(const string& student_dir, const string& official_data_path) {
  printf("Testing student: %s\n", student_dir.c_str());
  // 遍历每个子目录
  vector<int> problem_scores;
  for (auto [problem_name, sample_count] : problem_samples) {
    string problem_dir = student_dir + "/" + problem_name;
    int problem_score = TestOneProblem(problem_dir, official_data_path);
    problem_scores.push_back(problem_score);
  }
  return {problem_scores[0], problem_scores[1], problem_scores[2], problem_scores[3]};
}

void init() {
  // 对于一道题有几个样例，手动填写
  problem_samples["number"] = 25;   // number
  problem_samples["polygon"] = 25;  // polygon
  problem_samples["seat"] = 20;     // seat
  problem_samples["xor"] = 20;      // xor
}

int main(int argc, char** argv) {
  // if (argc != 3) {
  //   printf("Usage: ./run_score <考生代码路径> <官方数据路径>\n");
  //   return 0;
  // }
  string user_code_path = "/Users/tiankonguse-m3/project/github/data/1/answers";
  string official_data_path = "/Users/tiankonguse-m3/project/github/data/CSP-J";

  init();

  // 获取当前程序的路径，保存起来，方便创建临时目录
  main_path = filesystem::current_path().string();
  system("mkdir -p ./tmpfile");
  printf("Main path: %s\n", main_path.c_str());

  unordered_map<string, tuple<int, int, int, int>> student_scores;
  // 遍历考生目录
  for (const auto& entry : filesystem::directory_iterator(user_code_path)) {
    if (entry.is_directory()) {
      string student_dir = entry.path().string();
      // 提取学生编号
      string student_id = filesystem::path(student_dir).filename().string();
      auto scores = TestOneStudent(student_dir, official_data_path);
      int all_score = (get<0>(scores) + get<1>(scores) + get<2>(scores) + get<3>(scores));
      printf("  Student %s allScore=%d, problem score: %d %d %d %d\n", student_dir.c_str(), all_score, get<0>(scores),
             get<1>(scores), get<2>(scores), get<3>(scores));

      student_scores[student_id] = scores;
    } else {
      printf("Skipping non-directory entry: %s\n", entry.path().string().c_str());
    }
  }

  vector<string> problem_ids;
  for (auto& [problem_id, _] : problem_samples) {
    problem_ids.push_back(problem_id);
  }
  printf("%10s %10s %10s %10s %10s %10s\n", "StudentID", "AllScore", problem_ids[0].c_str(), problem_ids[1].c_str(),
         problem_ids[2].c_str(), problem_ids[3].c_str());
  for (auto& [student_id, scores] : student_scores) {
    int all_score = (get<0>(scores) + get<1>(scores) + get<2>(scores) + get<3>(scores));
    printf("%10s %10d %10d %10d %10d %10d\n", student_id.c_str(), all_score, get<0>(scores), get<1>(scores),
           get<2>(scores), get<3>(scores));
  }
  return 0;
}