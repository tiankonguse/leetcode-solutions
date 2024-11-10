/*
ID: tiankonguse
TASK: butter
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "butter"

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

int N, P, C;
vector<int> cows;
vector<vector<pair<int, int>>> g;
vector<vector<int>> allDis;

void Primer(int u) {
  auto& dis = allDis[u];
  dis.resize(P, INT_MAX);
  dis[u] = 0;
  min_queue<pair<int, int>> que;
  que.push({0, u});

  while (!que.empty()) {
    auto [ud, u] = que.top();
    que.pop();
    if (dis[u] != ud) continue;  // 有更优解，已经计算过了
    for (auto [v, vd] : g[u]) {
      if (ud + vd < dis[v]) {
        dis[v] = ud + vd;
        que.push({dis[v], v});
      }
    }
  }
}

void Solver() {  //
  scanf("%d%d%d", &N, &P, &C);
  cows.resize(N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &cows[i]);
    cows[i]--;
  }
  g.resize(P);
  for (int i = 0; i < C; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    u--;
    v--;
    g[u].push_back({v, c});
    g[v].push_back({u, c});
  }
  allDis.resize(P);
  for (int i = 0; i < P; i++) {
    Primer(i);
  }
  int ans = INT_MAX;
  for (int u = 0; u < P; u++) {  // 枚举中心
    int sum = 0;
    for (auto v : cows) {
      sum += allDis[u][v];
    }
    ans = min(ans, sum);
  }
  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/