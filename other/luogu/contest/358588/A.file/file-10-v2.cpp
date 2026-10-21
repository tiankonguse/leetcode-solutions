/*
ID: tiankonguse
TASK: file
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17722?contestId=358588
PATH: P17722 [SCP-S 2026] 档案 / file
submission: https://www.luogu.com.cn/record/304516548
*/
#define TASK "file"
#define TASKEX "-10-v2"

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

ll n, m;
unordered_map<ll, int> mp;
vector<ll> A;
vector<vector<ll>> B;

/*
基本思路：
测试点 1~2: m<=7
思路2：排列组合优化 m^m -> m!
复杂度：m! * (L + m*L*log(L) + L)
得分： 10 分

*/

vector<int> vis;  // 记录当前排列
int allCnt = 0;
ll ans = 0;
void UpdateAns() {  //
  vector<ll> a = A;
  a.reserve(allCnt);
  ll sum = 0;
  for (int b : vis) {
    for (int j = 0; j < B[b].size(); j++) {
      a.push_back(B[b][j]);
    }
    sort(a.begin(), a.end());
    for (int i = 1; i <= a.size(); i++) {
      if (mp.count(a[i - 1])) {
        sum += i;
      }
    }
  }
  ans = min(ans, sum);
}

void Dfs(const int leftNum) {
  if (leftNum == 0) {
    // 计算当前排列的代价
    UpdateAns();
    return;
  }
  for (int i = 0; i < leftNum; i++) {
    swap(vis[leftNum - 1], vis[i]);
    Dfs(leftNum - 1);
    swap(vis[leftNum - 1], vis[i]);
  }
}

void Solver() {  //
  scanf("%lld%lld", &n, &m);
  A.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
    mp[A[i]]++;
  }

  // sort(A.begin(), A.end());

  allCnt = n;
  B.resize(m);
  vis.resize(m);
  for (int i = 0; i < m; i++) {
    vis[i] = i;
    ll L;
    scanf("%lld", &L);
    allCnt += L;
    B[i].resize(L);
    for (int j = 0; j < L; j++) {
      ll x;
      scanf("%lld", &x);
      B[i][j] = x;
    }
    // sort(B[i].begin(), B[i].end());
  }

  // 暴力求 m 的排列
  ans = INT64_MAX;
  Dfs(m);

  printf("%lld\n", ans);
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
