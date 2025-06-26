/*
ID: tiankonguse
TASK: transmit
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8820
PATH: P8820 [CSP-S 2022] 数据传输
submission: https://www.luogu.com.cn/record/221304194
评测分数:
*/
#define TASK "transmit"
#define TASKEX "-matrix"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
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

// constexpr int INF = 1 << 30;
// constexpr ll INFL = 1LL << 60;
// constexpr ll MOD = 1000000007;

// const double pi = acos(-1.0), eps = 1e-7;
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
// const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll e17 = 1e16;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

const int maxn = 200015;
const int maxn_log = 20;  // 17.6096765414

int kMatrixSize = 6;
template <int N>
struct Matrix {
  ll a[N][N];
  Matrix() {  //
    Init();
  }
  void Init() {
    for (int i = 0; i < kMatrixSize; i++) {
      for (int j = 0; j < kMatrixSize; j++) {
        a[i][j] = e17;
      }
    }
  }

  Matrix<N> operator*(const Matrix<N>& B) const {
    Matrix<N> ret;
    ret.Init();
    for (int i = 0; i < kMatrixSize; i++)
      for (int j = 0; j < kMatrixSize; j++)
        for (int k = 0; k < kMatrixSize; k++) {
          ret.a[i][j] = std::min(ret.a[i][j], a[i][k] + B.a[k][j]);
        }
    return ret;
  }
  Matrix<N>& operator=(const Matrix<N>& B) {
    for (int i = 0; i < kMatrixSize; i++) {
      for (int j = 0; j < kMatrixSize; j++) {
        a[i][j] = B.a[i][j];
      }
    }
    return *this;
  }
};
Matrix<5> mat3[maxn][maxn_log];

vector<int> g[maxn];  // 有向树
ll f[maxn][maxn_log], dep[maxn], minChild[maxn];
// LL  minChildIndex[maxn];
// ll F[maxn][maxn_log];  // 区间最小路径和
// ll costSum[maxn] = {0};
vector<int> G[maxn];  // 无向树
ll costs[maxn] = {0};
int n, Q, k;

void InitMat(int v, int u) {
  auto& mat = mat3[v][0];
  mat.Init();
  for (int i = 0; i < kMatrixSize; i++) {
    mat.a[i][0] = costs[u];
  }
  mat.a[0][1] = 0;
  mat.a[0][2] = mat.a[1][2] = mat.a[2][2] = minChild[u];
  mat.a[1][3] = 0;
  mat.a[2][4] = 0;
}

void DfsRMQ(const int u) {
  for (const int v : g[u]) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    dep[v] = dep[u] + 1;
    f[v][0] = u;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
    InitMat(v, u);
    for (int i = 1; i < maxn_log; i++) {
      f[v][i] = f[f[v][i - 1]][i - 1];
      mat3[v][i] = mat3[v][i - 1] * mat3[f[v][i - 1]][i - 1];
    }
    DfsRMQ(v);
  }
}

void DfsInit(int u, int fa) {
  minChild[u] = costs[fa];
  for (int v : G[u]) {
    if (v == fa) continue;
    g[u].push_back(v);
    DfsInit(v, u);
    if (minChild[u] > costs[v]) {
      minChild[u] = costs[v];
    }
  }
}

const int kHead = 0;
void Init() {
  if (k == 1) {
    kMatrixSize = 1;
  } else if (k == 2) {
    kMatrixSize = 2;
  } else {
    kMatrixSize = 5;
  }
  DfsInit(0, -1);
  memset(f[0], 0, sizeof f[0]);
  InitMat(0, 0);
  DfsRMQ(0);
  // memset(costSum, 0, sizeof costSum);
  // DfsCost(0);
}

int Lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
    if (d & (1 << i)) {
      u = f[u][i];
      d = d ^ (1 << i);
    }
  }
  if (u == v) return u;
  for (int i = maxn_log - 1; i >= 0; i--) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  return f[u][0];
}

void PreKCost(Matrix<5>& U, int u, int d) {
  // while (d) {
  //   U = U * mat3[u][0];
  //   d--;
  //   u = f[u][0];
  // }
  for (int i = maxn_log - 1; d && i >= 0; i--) {
    if (d & (1 << i)) {
      U = U * mat3[u][i];
      d = d ^ (1 << i);
      u = f[u][i];
    }
  }
}

ll PathCostSumCommon(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);  // 保障 u 是深度更深的, 即 v 可能是 lca
  }
  int lca = Lca(u, v);
  Matrix<5> U, V;
  U.a[0][0] = costs[u];
  V.a[0][0] = costs[v];
  PreKCost(U, u, dep[u] - dep[lca]);
  PreKCost(V, v, dep[v] - dep[lca]);
  ll ans = e17;
  MyPrintf("k=%d kMatrixSize=%d\n", k, kMatrixSize);
  ans = min(ans, U.a[0][0] + V.a[0][0] - costs[lca]);  // 两个树根重合
  MyPrintf("U.a[0][0]=%lld,V.a[0][0]=%lld costs[lca]=%lld ans=%lld\n", U.a[0][0], V.a[0][0], costs[lca], ans);
  if (k == 3) {  // 根的最小儿子重合
    ll tmpAns = U.a[0][2] + V.a[0][2] - minChild[lca];
    MyPrintf("U.a[0][2]=%lld,V.a[0][2]=%lld minChild[lca]=%lld ans=%lld\n", U.a[0][2], V.a[0][2], minChild[lca],
             tmpAns);
    ans = min(ans, tmpAns);
  }

  for (int i = 0; i < kMatrixSize; i++) {
    for (int j = 0; j < kMatrixSize; j++) {
      int ii = (i + 1) / 2;
      int jj = (j + 1) / 2;
      if (ii + jj <= k) {  // 一步到位
        MyPrintf("U.a[0][%d]=%lld,V.a[0][%d]=%lld sum=%lld\n", i, U.a[0][i], j, V.a[0][j], U.a[0][i] + V.a[0][j]);
        ans = min(ans, U.a[0][i] + V.a[0][j]);
      }
    }
  }
  return ans;
}

void Solver() {  //
  scanf("%d%d%d", &n, &Q, &k);
  costs[0] = e17;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &costs[i]);
    MyPrintf("costs[%d]=%lld\n", i, costs[i]);
  }
  G[0].push_back(1);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  Init();
  while (Q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    MyPrintf("u=%d,v=%d\n", u, v);
    printf("%lld\n", PathCostSumCommon(u, v));
    // break;
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/