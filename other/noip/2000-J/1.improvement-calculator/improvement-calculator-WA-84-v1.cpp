/*
ID: tiankonguse
TASK: improvement-calculator
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "improvement-calculator"
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
int debug_assert = 1;
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

char str[max5];
string S;
string var;
struct Node {
  int sign;
  ll val;
  int flag;  // 是否是变量
};
vector<Node> exprs;

Node ParseNode(const char*& p) {
  Node node;
  node.sign = 1;
  node.val = 0;
  node.flag = 0;
  if (*p == '-') {
    node.sign = -1;
    p++;
  }
  if (*p == '+') {
    node.sign = 1;
    p++;
  }
  while (isdigit(*p)) {
    node.val = node.val * 10 + (*p - '0');
    p++;
  }
  int varFlag = 1;
  if (var.empty()) {
    varFlag = 0;
  }
  if(isalpha(*p) && node.val == 0){
    node.val = 1;
  }

  while (isalpha(*p)) {
    if (varFlag == 0) {
      var.push_back(*p);
    }
    node.flag = 1;
    p++;
  }
  return node;
}
void Parse(const char* p, int sign) {
  while (*p) {
    Node node = ParseNode(p);
    MyPrintf("node: %d %lld %d, left=%s\n", node.sign, node.val, node.flag, p);
    node.sign *= sign;
    exprs.push_back(node);
  }
}
void Parse() {  //
  int n = S.size();
  int pos = S.find('=');
  string left = S.substr(0, pos);
  string right = S.substr(pos + 1);
  MyPrintf("left: %s\n", left.c_str());
  MyPrintf("right: %s\n", right.c_str());
  exprs.clear();
  Parse(left.data(), 1);
  Parse(right.data(), -1);

  ll sumNum = 0, sumVar = 0;
  for (auto& node : exprs) {
    if (node.flag) {
      sumVar += node.sign * node.val;
    } else {
      sumNum += node.sign * node.val;
    }
  }
  MyPrintf("sumNum: %lld, sumVar: %lld\n", sumNum, sumVar);
  ll ans = -1000 * sumNum / sumVar;
  printf("%s=%.3f\n", var.c_str(), ans * 1.0/1000);
}
void Solver() {  //
  scanf("%s", str);
  S = str;
  Parse();
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
  MyPrintf("my 用时: %.0lfms\n", costTime);
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
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  if (USACO_TASK_FILE != 0) {
    MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
  }
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
