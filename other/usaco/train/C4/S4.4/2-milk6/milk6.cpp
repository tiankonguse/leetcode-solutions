/*
ID: tiankonguse
TASK: milk6
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "milk6"
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

/****************************************\
* Author : ztx
* Title  :
* ALG    : ISAP
* CMT    :
* Time   :
\****************************************/

#include <bits/stdc++.h>

typedef long long ll;

#define maxN 33
#define maxM 5500
#define infi INT_MAX

vector<int> flowIndexToId;
struct FST {
  int to, next;
  ll flow;
  int id;
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
  inline void AddEdge(int u, int v, ll cap, int id) {
    e[++tote].to = v;
    e[tote].flow = cap;
    e[tote].id = id;
    e[tote].next = star[u];
    star[u] = tote;
    flowIndexToId[id] = tote;

    e[++tote].to = u;
    e[tote].flow = 0;
    e[tote].id = id;
    e[tote].next = star[v];
    star[v] = tote;
  }

  void Set(int id, ll cost) {
    const int i = flowIndexToId[id];
    e[i].flow = cost;
    e[i ^ 1].flow = 0;
  }
  ll Get(int id) { return e[flowIndexToId[id]].flow; }

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

int n, m;
vector<vector<tuple<int, ll, int>>> g;
vector<tuple<int, int, ll>> edges;
vector<int> fullEdges;

bool Check(const int s, const int t) {
  vector<int> flag(n, 0);
  queue<int> que;
  que.push(s);
  flag[s] = 1;
  while (!que.empty()) {
    const auto u = que.front();
    que.pop();
    for (auto [v, c, id] : g[u]) {
      if (flag[v]) continue;
      if (v == t) return true;
      que.push(v);
      flag[v] = 1;
    }
  }
  return false;
}

void Solver() {  //
  scanf("%d%d", &n, &m);
  g.resize(n);
  edges.resize(m);
  fullEdges.resize(m, 0);
  flowIndexToId.resize(maxM, 0);

  networkFlow.Init(n);

  for (int i = 0; i < m; i++) {
    int s, e, c;
    scanf("%d%d%d", &s, &e, &c);
    s--, e--;
    edges[i] = {s, e, c};
    g[s].push_back({e, c, i});

    networkFlow.AddEdge(s, e, c, i);
  }

  int S = 0;
  int T = n - 1;

  // 先判断是否联通
  if (!Check(S, T)) {
    printf("0 0\n");
    return;
  }

  // 第一遍最大流，计算最大成本
  const ll minCost = networkFlow.ISAP(S, T);

  // 第二步，对于不满的流设置为inf，满流设置为1
  for (int id = 0; id < m; id++) {
    if (networkFlow.Get(id) == 0) {
      fullEdges[id] = 1;
      networkFlow.Set(id, 1);
    } else {
      networkFlow.Set(id, inf);
    }
  }
  const ll minCut = networkFlow.ISAP(S, T);

  vector<int> ans;
  int leftCut = minCut;
  for (int id = 0; leftCut > 0 && id < m; id++) {  // 尝试关闭 id
    if (!fullEdges[id]) continue;
    for (int i = 0; i < m; i++) {
      if (fullEdges[i]) {
        networkFlow.Set(i, 1);
      } else {
        networkFlow.Set(i, inf);
      }
    }
    for (auto i : ans) {
      networkFlow.Set(i, 0);
    }
    networkFlow.Set(id, 0);
    const ll cut = networkFlow.ISAP(S, T);
    if (1 + cut == leftCut) {
      ans.push_back(id);
      leftCut--;
    }
  }

  printf("%lld %lld\n", minCost, minCut);
  for (auto id : ans) {
    printf("%d\n", id + 1);
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