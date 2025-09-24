/*
ID: tiankonguse
TASK: call
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7077
PATH:  P7077 [CSP-S2020] 函数调用
submission:
*/
#define TASK "call"
#define TASKEX ""

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
const ll mod9 = 998244353;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
#ifdef USACO_LOCAL_JUDGE
// #define USACO_TASK_FILE 3
#define TASKNO 3
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif

  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
}

vector<ll> A;
vector<ll> T;
vector<ll> P;
vector<ll> V;
vector<ll> innerMul;
vector<ll> inDeg;
vector<vector<ll>> G;
int n, m, q;

void Input() {
  scanf("%d", &n);
  A.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &A[i]);
  }
  scanf("%d", &m);
  T.resize(m + 1);
  P.resize(m + 1);
  V.resize(m + 1);
  innerMul.resize(m + 1, 1);
  G.resize(m + 1);
  inDeg.resize(m + 1);
  for (int i = 1; i <= m; i++) {
    scanf("%lld", &T[i]);
    if (T[i] == 1) {
      scanf("%lld%lld", &P[i], &V[i]);
    } else if (T[i] == 2) {
      scanf("%lld", &V[i]);
      innerMul[i] = V[i];
    } else {
      int q;
      scanf("%d", &q);
      G[i].resize(q);
      for (int j = 0; j < q; j++) {
        scanf("%lld", &G[i][j]);
        inDeg[G[i][j]]++;
      }
      std::reverse(G[i].begin(), G[i].end());
    }
  }
  scanf("%d", &q);
  G[0].resize(q);  // 询问也是一个函数，储存在 G[0] 中
  for (int i = 0; i < q; i++) {
    scanf("%lld", &G[0][i]);
  }
  std::reverse(G[0].begin(), G[0].end());
}

vector<int> orderedIndex;

void TopologicalSort() {
  orderedIndex.reserve(m + 1);
  orderedIndex.push_back(0);  // 0 是询问，也是根节点
  queue<int> que;
  for (int i = 1; i <= m; i++) {
    if (inDeg[i] == 0) {
      que.push(i);
    }
  }
  while (!que.empty()) {
    const int u = que.front();
    que.pop();
    orderedIndex.push_back(u);

    for (const auto v : G[u]) {
      inDeg[v]--;
      if (inDeg[v] == 0) {
        que.push(v);
      }
    }
  }
}

void CalNodeMul() {  // 计算每个节点自身的累计乘积
  for (int i = m; i >= 0; i--) {
    const int u = orderedIndex[i];
    for (const auto v : G[u]) {
      innerMul[u] = (innerMul[u] * innerMul[v]) % mod9;
    }
  }
}

vector<ll> afterMul;  // 计算每个节点后续的乘积
void calNodeCount() {
  afterMul.resize(m + 1);
  afterMul[0] = 1;
  for (int i = 0; i <= m; i++) {
    const int u = orderedIndex[i];
    ll cnt = afterMul[u];  // 处理到 u, 说明所有依赖 u 的节点都处理完了
    for (const auto v : G[u]) {
      afterMul[v] = (afterMul[v] + cnt) % mod9;
      cnt = (cnt * innerMul[v]) % mod9;
    }
  }
}

void Solver() {  //
  Input();
  TopologicalSort();
  CalNodeMul();
  calNodeCount();
  for (int i = 1; i <= n; i++) {
    A[i] = A[i] * innerMul[0] % mod9;
  }
  for (int i = 1; i <= m; i++) {
    if (P[i]) {  // 操作1，需要进行累加
      const int u = P[i];
      A[u] = (A[u] + V[i] * afterMul[i]) % mod9;
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%lld%c", A[i], i < n ? ' ' : '\n');
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t1 = std::chrono::steady_clock::now();
#endif
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
  }
#endif
  return 0;
}

/*

*/