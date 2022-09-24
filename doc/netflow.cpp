/****************************************\
* Author : ztx
* Title  :
* ALG    : ISAP
* CMT    :
* Time   :
\****************************************/

#include <cstdio>

typedef long long ll;

#include <cstring>

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
#define maxN ____LL
#define maxM ____LL
#define infi 0x________LL

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

  void Init() {
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
  ll ISAP() {
    ll ret = 0;
    memset(vh, 0, sizeof(vh));
    memset(h, 0, sizeof(h));
    vh[S] = N;
    while (h[S] < N) ret += Dfs(S, infi);
    return ret;
  }
};

NetworkFlow networkFlow;
