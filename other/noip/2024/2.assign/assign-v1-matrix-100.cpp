/*
ID: tiankonguse
TASK: assign
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "assign"
#define TASKEX "-v1-matrix"

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
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 3
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
  mint operator+(const mint& b) const { return mint((x + b.x) % mod); }
  mint operator-(const mint& b) const { return mint((x - b.x % mod + mod) % mod); }
  mint operator*(const mint& b) const { return mint((x * b.x) % mod); }
  mint operator*(const ll& b) const { return mint((x * b) % mod); }
  mint operator/(const ll& b) const { return mint((x * inv(b, mod)) % mod); }
  mint operator=(const mint& b) {
    x = b.x;
    return *this;
  }
  mint operator+=(const mint& b) {
    x = (x + b.x) % mod;
    return *this;
  }
  mint operator+=(const ll& b) {
    x = (x + b) % mod;
    return *this;
  }
  mint operator~() const { return mint(qpow(x, mod - 2, mod)); }
};

struct Matrix {
  ll P;
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 1) : sz(sz) {  //
    init(sz);
  }
  void init(int n, ll p = mod) {
    P = p;
    sz = n;
    a.clear();
    a.resize(n, vector<ll>(n, 0));
  }
  void _union() {
    int l = sz;
    while (l--) {
      a[l][l] = 1;
    }
  }
  Matrix operator*(const Matrix& B) const {
    Matrix ret(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        for (int k = 0; k < sz; k++) ret.a[i][j] = (ret.a[i][j] + a[i][k] * B.a[k][j]) % P;
    return ret;
  }
  Matrix pow(ll k) const {
    Matrix ret(sz);
    Matrix A = *this;
    ret._union();
    while (k) {
      if (k & 1) ret = ret * A;
      A = A * A;
      k >>= 1;
    }
    return ret;
  }
  ll Sum() const {
    ll ret = 0;
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < sz; j++) {
        ret = (ret + a[i][j]) % P;
      }
    }
    return ret;
  }
};

map<ll, ll> H;
void SolverEx() {
  ll n, m, v;
  scanf("%lld%lld%lld", &n, &m, &v);
  H.clear();
  bool noAns = 0;
  for (int i = 0; i < m; i++) {
    ll c, d;
    scanf("%lld%lld", &c, &d);
    if (H.count(c)) {
      if (H[c] != d) {
        noAns = 1;
      }
    } else {
      H[c] = d;
    }
  }
  if (noAns) {
    printf("0\n");
    return;
  }
  mint preVal1 = 1;
  ll prePos = 1;
  bool first = 1;

  Matrix matV(2);
  matV.a[0][0] = v;
  matV.a[1][0] = 0;
  matV.a[0][1] = (v * (v - 1)) % mod;
  matV.a[1][1] = (v * v) % mod;

  Matrix matC(2);
  matC.a[0][0] = 1;
  matC.a[1][0] = 0;
  matC.a[0][1] = (v * (v - 1)) % mod;
  matC.a[1][1] = (v * v) % mod;

  for (const auto& [p, _] : H) {
    const ll len = p - prePos;
    MyPrintf("处理点 p=%lld prePos=%lld len=%lld v=%lld\n", p, prePos, len, v);
    if (first == 1) {  // TYPE_0 -> TYPE_1
      first = 0;
      preVal1 = preVal1 * qpow(v, len, mod) * qpow(v, len, mod);
    } else {
      Matrix mat(2);
      mat.a[0][0] = preVal1.x;
      Matrix tmp = mat * matV.pow(len - 1) * matC;
      preVal1.x = (tmp.a[0][0] + tmp.a[0][1]) % mod;
    }
    prePos = p;
    MyPrintf("  preVal1.x=%lld\n", preVal1.x);
  }
  // 处理最后一段
  const ll len = n - prePos;
  if (len > 0) {
    preVal1 = preVal1 * qpow(v, len, mod) * qpow(v, len, mod);
    MyPrintf("  last=%lld len=%lld\n", preVal1.x, len);
  }
  printf("%lld\n", preVal1.x);
}

void Solver() {  //
  int T;
  scanf("%d", &T);
  while (T--) {
    SolverEx();
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
