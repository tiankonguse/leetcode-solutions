/*
ID: tiankonguse
TASK: Cryptarithm
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1092
PATH:
submission: 从低位到高位暴力搜索
*/
#define TASK "Cryptarithm"
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
char s1[30], s2[30], s3[30];
int charToVal[30];
char valToChar[30];

bool Dfs1(const int p, const int carry);
bool Dfs2(const int p, const int carry);

bool Dfs3(const int p, const int carry) {
  const int c1 = s1[p] - 'A';
  const int c2 = s2[p] - 'A';
  const int c3 = s3[p] - 'A';
  const int sum = charToVal[c1] + charToVal[c2] + carry;
  const int val3 = sum % n;
  const int carry3 = sum / n;
  if (charToVal[c3] == -1) {
    charToVal[c3] = val3;
    valToChar[val3] = c3;
    if (Dfs1(p - 1, carry3)) {
      return true;
    }
    charToVal[c3] = -1;
    valToChar[val3] = 0;
    return false;
  } else {
    if (charToVal[c3] != val3) {
      return false;
    } else {
      return Dfs1(p - 1, carry3);
    }
  }
  return false;
}

bool Dfs2(const int p, const int carry) {
  const int c2 = s2[p] - 'A';
  if (charToVal[c2] != -1) {
    return Dfs3(p, carry);
  }
  for (int i = 0; i < n; i++) {
    if (valToChar[i] == 0) {
      charToVal[c2] = i;
      valToChar[i] = c2;
      if (Dfs3(p, carry)) {
        return true;
      }
      charToVal[c2] = -1;
      valToChar[i] = 0;
    }
  }
  return false;
}

bool Dfs1(const int p, const int carry) {
  if (p == -1) {
    if (carry == 0) {
      return true;
    } else {
      return false;
    }
  }
  const int c1 = s1[p] - 'A';
  if (charToVal[c1] != -1) {
    return Dfs2(p, carry);
  }
  for (int i = 0; i < n; i++) {
    if (valToChar[i] == 0) {
      charToVal[c1] = i;
      valToChar[i] = c1;
      if (Dfs2(p, carry)) {
        return true;
      }
      charToVal[c1] = -1;
      valToChar[i] = 0;
    }
  }
  return false;
}

void Solver() {  //
  scanf("%d", &n);
  scanf("%s%s%s", s1, s2, s3);
  memset(charToVal, -1, sizeof(charToVal));
  memset(valToChar, 0, sizeof(valToChar));
  Dfs1(n - 1, 0);
  for (int i = 0; i < n; i++) {
    printf("%d%c", charToVal[i], i == n - 1 ? '\n' : ' ');
  }
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
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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
