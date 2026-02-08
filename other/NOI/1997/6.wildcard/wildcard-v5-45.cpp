/*
ID: tiankonguse
TASK: wildcard
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8853
PATH:
submission:
*/
#define TASK "wildcard"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int n;
unordered_set<string> blockList;
unordered_map<string, int> allowList;
vector<string> datas;
vector<string> wildcards;
char str[22];
char op[5];

int skipFlag = 0;
void Dfs(const char* p, string& wildcard) {
  // if(wildcard.size() > 8) return; // 剪枝
  if (*p == '\0') {
    if (skipFlag == 1 && blockList.count(wildcard)) {
      return;
    }
    wildcards.push_back(wildcard);
    return;
  }
  const char val = *p;
  // 第一步：保持不变
  wildcard.push_back(val);
  Dfs(p + 1, wildcard);
  wildcard.pop_back();

  // 第二步，是 *， 进行匹配
  if ((!wildcard.empty()) && wildcard.back() == '*') {
    // ?* 等价与 *?， 故 * 后面不能跟 ?
    // ** 等价与 *， 故 * 后面不能跟 *
    Dfs(p + 1, wildcard);
  } else {
    // 第三步：替换为 ?
    wildcard.push_back('?');
    Dfs(p + 1, wildcard);
    wildcard.pop_back();

    // 第四步：替换为 *
    wildcard.push_back('*');
    Dfs(p + 1, wildcard);
    wildcard.pop_back();

    // 还有一种情况是插入一个空的 *
    wildcard.push_back('*');
    Dfs(p, wildcard);
    wildcard.pop_back();
  }
}

void CalWildcard(const char* p) {  //
  wildcards.clear();
  string wildcard;
  Dfs(p, wildcard);
  sort(wildcards.begin(), wildcards.end());
  wildcards.erase(unique(wildcards.begin(), wildcards.end()), wildcards.end());
}
void Solver() {  //
  scanf("%d", &n);
  datas.clear();
  blockList.clear();
  allowList.clear();
  wildcards.reserve(1024);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", str, op);
    if (op[0] == '+') {
      datas.push_back(str);
    } else {
      CalWildcard(str);
      for (const auto& wildcard : wildcards) {
        blockList.insert(wildcard);
      }
    }
  }
  skipFlag = 1;
  MyPrintf("datas=%d blockList: %d\n", int(datas.size()), int(blockList.size()));
  for (const auto& word : datas) {
    CalWildcard(word.data());
    MyPrintf("word: %s wildcards=%d\n", word.c_str(), int(wildcards.size()));
    for (const auto& wildcard : wildcards) {
      if (!blockList.count(wildcard)) {
        if (wildcard == "E*") {
          MyPrintf("word=%s wildcard: %s\n", word.data(), wildcard.c_str());
        }
        allowList[wildcard]++;
      }
    }
  }
  int ans = 0;
  string ansWord;
  for (auto& [wildcard, cnt] : allowList) {
    if (cnt > ans || (cnt == ans && wildcard.size() < ansWord.size())) {
      ans = cnt;
      ansWord = wildcard;
    }
  }
  printf("%d\n%s\n", ans, ansWord.c_str());
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
