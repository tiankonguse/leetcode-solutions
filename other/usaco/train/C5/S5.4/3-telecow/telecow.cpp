/*
ID: tiankonguse
TASK: telecow
LANG: C++
MAC EOF: ctrl+D
DESC: Vertex connectivity 顶点连通性 - 拆点，最大流
*/
#define TASK "telecow"
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

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

#define maxN 222
#define maxM 2200
#define infi INT_MAX

struct FST {
  int to, next;
  ll flow;
};  // 邻接表
class NetworkFlow {
 public:
  int N, S, T;
  int h[maxN], vh[maxN];

  struct FST e[maxM << 1];
  int star[maxN], tote;

  void Init(const int n) {
    N = n;
    memset(star, 0, sizeof(star));
    tote = 1;
  }
  inline void AddEdge(int u, int v, ll cap) {
    e[++tote].to = v;
    e[tote].flow = cap;
    e[tote].next = star[u];
    star[u] = tote;
    e[++tote].to = u;
    e[tote].flow = 0;
    e[tote].next = star[v];
    star[v] = tote;
  }

  ll Dfs(int u, ll flowu) {
    int p, tmp = h[u] + 1;
    ll flow = 0, flowv;
    if (u == T) return flowu;
    for (p = star[u]; p; p = e[p].next) {
      if (e[p].flow && (h[e[p].to] + 1 == h[u])) {
        flowv = Dfs(e[p].to, min(flowu - flow, e[p].flow));
        flow += flowv;
        e[p].flow -= flowv;
        e[p ^ 1].flow += flowv;
        if (flow == flowu || h[S] == N) return flow;
      }
    }
    for (p = star[u]; p; p = e[p].next)
      if (e[p].flow) tmp = min(tmp, h[e[p].to]);
    if (--vh[h[u]] == 0)
      h[S] = N;
    else
      ++vh[h[u] = tmp + 1];
    return flow;
  }

 public:
  ll ISAP(const int s, const int t) {
    S = s;
    T = t;
    ll ret = 0;
    memset(vh, 0, sizeof(vh));
    memset(h, 0, sizeof(h));
    vh[S] = N;
    while (h[S] < N) ret += Dfs(S, infi);
    return ret;
  }
};

NetworkFlow networkFlow;

int n, m, S, T;
vector<vector<int>> g;
int N;

ll RunFlow() {
  networkFlow.Init(N);
  for (int u = 1; u < N; u++) {
    for (int v = 1; v < N; v++) {
      if (g[u][v]) {
        networkFlow.AddEdge(u, v, g[u][v]);
      }
    }
  }
  return networkFlow.ISAP(S, T);
}

void Solver() {  //
  scanf("%d%d%d%d", &n, &m, &S, &T);
  N = 2 * n + 1;
  g.resize(N, vector<int>(N, 0));
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a][b] = 1;
    g[b][a] = 1;
  }
  // 拆点
  for (int u = 1; u <= n; u++) {
    if (u == S || u == T) continue;
    const int uu = u + n;

    // v<-->u =>  v->u<->uu->v
    for (int v = 1; v < N; v++) {
      if (g[u][v]) {
        g[u][v] = 0;
        g[uu][v] = 1;
      }
    }
    g[u][uu] = 1;
    g[uu][u] = 1;
  }
//   printf("i=%d: ", 0);
//   for (int j = 1; j < N; j++) {
//     printf("%d ", j);
//   }
//   printf("\n");
//   for (int i = 1; i < N; i++) {
//     printf("i=%d: ", i);
//     for (int j = 1; j < N; j++) {
//       printf("%d ", g[i][j]);
//     }
//     printf("\n");
//   }

  const ll maxFlow = RunFlow();
  int leftFlow = maxFlow;
  vector<ll> path;
  for (int u = 1; leftFlow > 0 && u <= n; u++) {  // 枚举删除顶点
    if (u == S || u == T) continue;
    int uu = u + n;
    g[u][uu] = 0;
    g[uu][u] = 0;
    ll childFlow = RunFlow();
    if (childFlow + 1 == leftFlow) {
      path.push_back(u);
      leftFlow--;
    } else {
      g[u][uu] = 1;
      g[uu][u] = 1;
    }
  }
  printf("%lld\n", maxFlow);
  for (ll i = 0; i < maxFlow; i++) {
    printf("%lld%c", path[i], i + 1 == maxFlow ? '\n' : ' ');
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/