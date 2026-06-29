/*
ID: tiankonguse
TASK: count-words
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1026
PATH: ./count-words.md
submission:
*/
#define TASK "count-words"
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
#define USACO_TASK_FILE 2
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

string S;
char buf[30];
vector<string> words;
ll dp[222][44];
ll dp2[222][222];
bool Check(const int l, const int r) {  //
  const int len = r - l + 1;
  for (const auto& word : words) {
    if (word.length() > len) continue;
    if (strncmp(S.c_str() + l, word.c_str(), word.length()) == 0) {
      return true;
    }
  }
  return false;
}
ll Count(const int l, const int r) {  //
  if (l > r) return 0;
  ll& ans = dp2[l][r];
  if (ans != -1) {
    return ans;
  }
  ans = Count(l + 1, r);
  if (Check(l, r)) {
    ans++;
  }
  MyPrintf("Count(%d, %d) = %lld  str=%s\n", l, r, ans, S.substr(l, r - l + 1).c_str());
  return ans;
}
ll Dfs(const int n, const int k) {
  if (n < k) return 0;
  if (k == 0) return 0;
  ll& ans = dp[n][k];
  if (ans != -1) {
    return ans;
  }
  ans = 0;
  for (int i = k; i <= n; i++) {
    ans = max(ans, Dfs(i - 1, k - 1) + Count(i, n));
  }
  MyPrintf("Dfs(%d, %d) = %lld\n", n, k, ans);
  return ans;
}
/*

thisisabookyouareaoh

*/
void Solver() {  //
  int p, k, m;
  scanf("%d%d", &p, &k);
  S.push_back(' ');
  int n = 0;
  while (p--) {
    scanf("%s", buf);
    S.append(buf);
    n += strlen(buf);
  }
  scanf("%d", &m);
  while (m--) {
    scanf("%s", buf);
    words.push_back(buf);
  }
  MyPrintf("words.size() = %d\n", words.size());
  for (auto& word : words) {
    MyPrintf("word=%s\n", word.c_str());
  }
  memset(dp, -1, sizeof(dp));
  memset(dp2, -1, sizeof(dp2));
  MyPrintf("S = %s n=%d k=%d\n", S.c_str(), n, k);
  printf("%lld\n", Dfs(n, k));
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
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
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
