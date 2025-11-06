/*
ID: tiankonguse
TASK: employ
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "employ"
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
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
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

int n, m;
char S[555];
vector<int> C;
vector<int> P;  // 排列，标记是否选择

ll ans = 0;

void Dfs(int p, int cnt) {  // cnt 代表之前已经选择了 cnt 个员工
  if (p == n + 1) {
    if (cnt >= m) {
      ans++;  // 找到一种合法的选择方案
    }
    return;
  }

  int c = (p - 1) - cnt;  // 前 p-1 天未被选择的员工数量

  // 第 p 天选择一个员工
  for (int i = 1; i <= n; i++) {
    if (P[i] == 0) {  // 员工 i 未被选择，尝试选择
      P[i] = 1;       // 选择员工 i
      if (S[p] == '1' && c < C[i]) {
        Dfs(p + 1, cnt + 1);
      } else {
        Dfs(p + 1, cnt);
      }
      P[i] = 0;  // 回溯，取消选择员工 i
    }
  }
}

// 快速幂
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}

// 模逆元，mod 必须为质数
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

/*
计算排列组合

A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

namespace Comb {

ll mod = 998244353;
vector<ll> A;
vector<ll> RA;

void InitA(int n, int mod) {
  A.resize(n + 1);
  A[0] = 1;

  for (int i = 1; i <= n; i++) {
    A[i] = (A[i - 1] * i) % mod;
  }

  RA.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    RA[i] = inv(A[i], mod);
  }
}

ll C(ll n, ll r, ll mod) {
  ll Anr = A[n] * RA[n - r] % mod;
  return Anr * RA[r] % mod;
}

ll P(ll n, ll r, ll mod) { return A[n] * RA[n - r] % mod; }

};  // namespace Comb

namespace DP {
// 状态定义 dp[i][mask][j] 前 i 天 的员工状态为 mask, 通过未面试 j 人的方案数
int dp[19][1 << 18][19];

int Dfs(int day, int mask, int nopass) {  //
  if (nopass < 0) return 0;
  int& ret = dp[day][mask][nopass];
  if (ret != -1) {
    return ret;
  }
  if (day == 0) {
    if (mask == 0 && nopass == 0) {
      return ret = 1;
    } else {
      return ret = 0;
    }
  }
  ret = 0;
  // 枚举第 day 天选择的员工
  for (int i = 0; i < n; i++) {
    if (mask & (1 << i)) {                   // 员工 i 被选择
      const int prevMask = mask ^ (1 << i);  // 去掉员工 i
      int prevNoPass = nopass;
      if (S[day] == '0') {  // 这天不可能招聘通过
        ret = (ret + Dfs(day - 1, prevMask, prevNoPass - 1)) % Comb::mod;
      } else {
        // 假设这名员工通过，则之前通过的人是 prevPass - 1
        if (prevNoPass < C[i + 1]) {  // 注意 C 数组是从 1 开始的
          ret = (ret + Dfs(day - 1, prevMask, prevNoPass)) % Comb::mod;
        }
        // 假设这名员工未通过，需要满足耐心值不够
        if (prevNoPass > 0 && prevNoPass - 1 >= C[i + 1]) {
          ret = (ret + Dfs(day - 1, prevMask, prevNoPass - 1)) % Comb::mod;
        }
      }
    }
  }

  return ret;
}

};  // namespace DP
void Solver() {  //
  scanf("%d%d", &n, &m);
  scanf("%s", S + 1);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    if (S[i] == '1') {
      sum++;
    }
  }
  C.resize(n + 1);
  int C0 = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &C[i]);
    if (C[i] == 0) {
      C0++;
    }
  }
  sort(C.begin() + 1, C.end());
  if (n <= 10) {
    P.resize(n + 1, 0);
    ans = 0;
    Dfs(1, 0);
    printf("%lld\n", ans);
    return;
  }
  if (n <= 18) {
    ll ans = 0;
    memset(DP::dp, -1, sizeof(DP::dp));
    for (int pass = m; pass <= n; pass++) {
      ans = (ans + DP::Dfs(n, (1 << n) - 1, n - pass)) % Comb::mod;
    }
    printf("%lld\n", ans);
    return;
  }
  if (n == m && sum < n) {
    // printf("n==m,sum<n,no pass\n");
    printf("0\n");
    return;
  }
  if (n - C0 < m) {
    // printf("n-C0<m, no pass\n");
    printf("0\n");
    return;
  }
  if (sum == n) {
    // printf("sum=n, all pass\n");
    // 特殊性质 A: 对于所有 i，均有 s[i]=1。
    // 所有人都面试通过，全排列，答案是 P(n, n)=n!
    ans = 1;
    for (int i = 1; i <= n; i++) {
      ans = (ans * i) % Comb::mod;
    }
    printf("%lld\n", ans);
    return;
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
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
    string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
    string fileOut = string(TASK) + to_string(fileIndex) + ".out";
    string cmd = string("diff -w " + fileAns + " " + fileOut);
    if (system(cmd.c_str())) {
      printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
    } else {
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
#endif
  return 0;
}
