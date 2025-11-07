/*
ID: tiankonguse
TASK: polygon
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "polygon"
#define TASKEX "-v2-80"

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
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#ifdef LOCAL_IO
#define USACO_TASK_FILE 25
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

ll n;
vector<ll> a;
const ll modV = 998244353;
void Solver() {  //
  scanf("%lld", &n);
  a.resize(n);
  ll maxV = 0;  // 特殊标记，大于 5000 的都当做 maxV 处理
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
    maxV = max(maxV, a[i]);
  }
  if (maxV == 1) {
    // 公式：2^n - C(n,0) - C(n, 1) - C(n, 2)
    ll ans = 1;
    for (int i = 0; i < n; i++) {
      ans = (ans * 2) % modV;
    }
    ans = (ans - 1 + modV) % modV;
    ans = (ans - n + modV) % modV;
    ans = (ans - (n * (n - 1) / 2) % modV + modV) % modV;
    printf("%lld\n", ans);
    return;
  }

  sort(a.begin(), a.end());
  ll ans = 0;
  ll sumV = n * maxV;
  vector<ll> dp(sumV + 1, 0);     // 子集和为 dp[i] 的方案数
  dp[0] = 1;                      // 空集
  for (int i = 1; i <= n; i++) {  // a[i] 作为最大边
    const ll v = a[i - 1];
    // 第 i 条边作为最大边，前面的边的子集和 大于 V 的个数
    for (int V = v + 1; V <= sumV; V++) {
      ans = (ans + dp[V]) % modV;
    }
    // 第 i 条边加入子集
    for (int V = sumV; V >= 0; V--) {
      const ll sum = V + v;
      if (sum > sumV) continue;
      dp[sum] = (dp[sum] + dp[V]) % modV;
    }
  }
  printf("%lld\n", ans);
}
/*
5
1 2 3 4 5
*/

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
  }
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int AC = 0;
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
    string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
    string fileOut = string(TASK) + to_string(fileIndex) + ".out";
    string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
    if (system(cmd.c_str())) {
      printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
#endif
  return 0;
}
