/*
ID: tiankonguse
TASK: ditch
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "ditch"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
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
#define maxM 333
#define infi INF

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

void Solver() {  //
  int n, m;
  scanf("%d%d", &m, &n);
  networkFlow.Init(n);
  for (int i = 0; i < m; i++) {
    int s, e, c;
    scanf("%d%d%d", &s, &e, &c);
    networkFlow.AddEdge(s - 1, e - 1, c);
  }
  printf("%lld\n", networkFlow.ISAP(0, n - 1));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/