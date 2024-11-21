/*
ID: tiankonguse
TASK: fence6
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence6"

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

int n;
vector<int> edges;
vector<set<int>> leftEdge;
vector<set<int>> rightEdge;

vector<vector<int>> g;
int ans = INT_MAX;

void UpdateAns(int tmp) {  //
  ans = min(ans, tmp);
}

void Solver(const int S) {
  const int baseCost = edges[S];
  vector<int> flag(n + 1, 0);
  min_queue<tuple<int, int, int>> que;
  flag[S] = edges[S];
  que.push({flag[S], S, -1});
  while (!que.empty()) {
    auto [cost, s, pre] = que.top();
    que.pop();
    if (!leftEdge[s].count(pre)) {
      for (auto t : leftEdge[s]) {
        if (flag[t]) {           // s-t 形成环
          UpdateAns(flag[s] + flag[t] - baseCost);
        } else {
          flag[t] = cost + edges[t];
          que.push({flag[t], t, s});
        }
      }
    }
    if (!rightEdge[s].count(pre)) {
      for (auto t : rightEdge[s]) {
        if (flag[t]) {           // s-t 形成环
          UpdateAns(flag[s] + flag[t] - baseCost);
        } else {
          flag[t] = cost + edges[t];
          que.push({flag[t], t, s});
        }
      }
    }
  }
}

void Solver() {  //
  scanf("%d", &n);
  edges.resize(n + 1, 0);
  leftEdge.resize(n + 1);
  rightEdge.resize(n + 1);

  for (int i = 1; i <= n; i++) {
    int s, l;
    scanf("%d%d", &s, &l);
    edges[s] = l;
    int n1, n2, id;
    scanf("%d%d", &n1, &n2);
    for (int j = 1; j <= n1; j++) {
      scanf("%d", &id);
      leftEdge[s].insert(id);
    }
    for (int j = 1; j <= n2; j++) {
      scanf("%d", &id);
      rightEdge[s].insert(id);
    }
  }

  // 预处理重边
  for (int i = 1; i <= n; i++) {
    if (edges[i] == -1) continue;  // 已删除
    vector<int> doubleEdges;
    for (auto l : leftEdge[i]) {
      if (rightEdge[i].count(l)) {
        doubleEdges.push_back(l);
      }
    }
    if (doubleEdges.empty()) {
      continue;
    }
    doubleEdges.push_back(i);
    sort(doubleEdges.begin(), doubleEdges.end(), [](int l, int r) {
      return edges[l] < edges[r];  // 权重从小到大排序
    });
    UpdateAns(edges[doubleEdges[0]] + edges[doubleEdges[1]]);
    const int s = doubleEdges[0];
    for (size_t j = 1; j < doubleEdges.size(); j++) {
      const int id = doubleEdges[i];
      edges[id] = -1;
      leftEdge[s].erase(id);
      rightEdge[s].erase(id);
    }
  }

  // 枚举每个边出发，可以找到的最小环
  for (int i = 1; i <= n; i++) {
    if (edges[i] == -1) continue;  // 已删除
    Solver(i);
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