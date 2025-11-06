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
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
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

const ll mod = 998244353;

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
struct mint {
  ll x;
  mint(ll x = 0) : x(x) {}
  mint operator+(const ll& b) const { return mint((x + b) % mod); }
  mint operator+(const mint& b) const { return mint((x + b.x) % mod); }
  mint& operator+=(const ll& b) { return (x = (x + b) % mod), *this; }
  mint& operator+=(const mint& b) { return (x = (x + b.x) % mod), *this; }
  mint operator*(const ll& b) const { return mint((x * b) % mod); }
  mint operator*(const mint& b) const { return mint((x * b.x) % mod); }
  mint& operator*=(const ll& b) { return (x = (x * b) % mod), *this; }
  mint& operator*=(const mint& b) { return (x = (x * b.x) % mod), *this; }
  mint& operator=(const mint& b) { return (x = b.x), *this; }
  mint& operator=(const ll& b) { return (x = b), *this; }
  mint operator~() const { return mint(qpow(x, mod - 2, mod)); }
};

const int N = 555;
mint fac[N], ifac[N];
mint A(int n, int m) { return n < m ? 0 : fac[n] * ifac[n - m]; }
mint C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m]; }

void Init() {
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = fac[i - 1] * i;
    ifac[i] = ~fac[i];
  }
}

int n, m;
char S[N];
vector<int> c;
vector<int> pre;                  //  S 的前缀和
vector<vector<vector<mint>>> dp;  // 前 i 个人，j 个挂，其中 c 大于 j 的有 k 个
// 定义：只有 j 变化时，才计算排列数。
// dp[n][x][k] 代表 前 n 个人，挂 x 个，挂的里面 c 大于 x 的有 k 个。 对于这个 k 个人，顺序不影响答案，所以有 k!
// 种排列方式。

void Solver() {  //
  Init();
  scanf("%d%d", &n, &m);
  scanf("%s", S + 1);
  c.resize(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    int v;
    scanf("%d", &v);
    c[v]++;
  }
  pre.resize(n + 2, 0);
  pre[0] = c[0];
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + c[i];
  }
  dp.resize(n + 1, vector<vector<mint>>(n + 1, vector<mint>(n + 1)));
  dp[0][0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= i; k++) {
        if (S[i + 1] == '1') {
          // 下个人不挂，忍耐度 C[i] 需要大于 j。j 不变，所以不需要计算排列数
          dp[i + 1][j][k + 1] += dp[i][j][k];
          // 下个人挂，忍耐度 C[i] 需要小于等于 j,  即在忍耐度为 [0, j] 之间选择1个人
          // 枚举 k 个忍耐度大于 j 的人中，有多少个忍耐度等于 j+1
          if (pre[j] >= i - k) {
            for (int t = 0; t <= min(k, c[j + 1]); t++) {  // 选择 t 个忍耐度等于 j+1 的人
              dp[i + 1][j + 1][k - t] += dp[i][j][k] * (pre[j] - (i - k)) * C(c[j + 1], t) * A(k, t);
            }
          }
        } else {  // S[i+1]=0, 下个人不管如何选择，必挂
          // 必挂，j 需要加 1
          for (int t = 0; t <= min(c[j + 1], k); t++) {  // 枚举之前 k 个人中，有多少个忍耐度等于 j+1
            // 情况1：选择 <= j+1 的人，此时 k 变为 k - t
            if (pre[j + 1] >= i - k + t) {
              dp[i + 1][j + 1][k - t] += dp[i][j][k] * (pre[j + 1] - (i - k + t)) * C(c[j + 1], t) * A(k, t);
            }
            // 情况2：选择 > j+1 的人，此时 k 变为 k - t + 1
            dp[i + 1][j + 1][k - t + 1] += dp[i][j][k] * C(c[j + 1], t) * A(k, t);
          }
        }
      }
    }
  }

  mint ans = 0;
  for (int j = 0; j <= n - m; j++) {  //  挂 j 个人，大于等于 j 的人数是 n - pre[j]
    int k = n - pre[j];
    ans += dp[n][j][k] * fac[k];
  }
  printf("%lld\n", ans.x);
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
