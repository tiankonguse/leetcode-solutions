/*
ID: tiankonguse
TASK: fence
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence"

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

class Solution {
 public:
  vector<int> edges;
  vector<vector<pair<int, int>>> g;
  int n, m;

  vector<int> vals;
  vector<int> nexts;
  vector<int> pres;
  int index = 0;
  int maxN = 0;

  int Add(int s) {
    int oldIndex = index;
    index++;
    vals[oldIndex] = s;
    return oldIndex;
  }

  void Bind(int a, int b) {
    nexts[a] = b;
    pres[b] = a;
  }

  int NextBack(int u) {
    while (g[u].size() > 0) {
      auto [v, i] = g[u].back();
      if (edges[i] == 0) {
        edges[i] = 1;
        g[u].pop_back();
        return v;
      } else {
        g[u].pop_back();
      }
    }
    return -1;
  }
  bool IsEmptyNode(int u) {
    while (g[u].size() > 0) {
      auto [v, i] = g[u].back();
      if (edges[i] == 0) {
        return false;
      } else {
        g[u].pop_back();
      }
    }
    return true;
  }

  // first -> second
  int Traver(int first) {
    while (g[vals[first]].size() > 0) {
      int c = NextBack(vals[first]);
      if (c == -1) break;
      const int second = Add(c);
      Bind(first, second);
      first = second;
    }
    return first;
  }

  int FindFirstNode() {
    int firstNoEmptyNode = 0;
    for (int i = 1; i <= maxN; i++) {
      if (g[i].size() == 0) continue;
      if (firstNoEmptyNode == 0) firstNoEmptyNode = i;
      if (g[i].size() % 2 == 1) {
        return i;
      }
    }
    return firstNoEmptyNode;  // 如果没有奇数度数，则使用第一个最小节点当做出发位置
  }
  vector<int> ans;

 public:
  const vector<int>& findItinerary(const int n,
                                   const vector<pair<int, int>>& tickets) {  //
    m = tickets.size();
    g.resize(n + 1);
    edges.resize(m + 1, 0);
    for (int i = 0; i < m; i++) {
      auto [a, b] = tickets[i];
      g[a].push_back({b, i});
      g[b].push_back({a, i});
      maxN = max(maxN, max(a, b));
    }
    for (int i = 1; i <= maxN; i++) {
      sort(g[i].begin(), g[i].end(), [](auto a, auto b) { return a > b; });
    }

    vals.resize(m + 10, -1);
    nexts.resize(m + 10, -1);
    pres.resize(m + 10, -1);

    int s = FindFirstNode();
    const int first = Add(s);
    const int last = Traver(first);
    while (index <= m) {
      // 从最后一个向前找到最后一个非空节点
      int mid = last;
      while (mid != -1 && vals[mid] != -1 && IsEmptyNode(vals[mid])) {
        mid = pres[mid];
      }
      // mid -> first
      int val = NextBack(vals[mid]);
      const int midFirst = Add(val);  // 首个节点
      int midLast = Traver(midFirst);
      // first-> ... -> mid -> ... last
      // mid : midFirst -> ... -> midLast
      const int nextMid = nexts[mid];
      Bind(midLast, nextMid);
      Bind(mid, midFirst);
    }

    ans.reserve(m + 1);
    int it = first;
    while (it != -1 && vals[it] != -1) {
      ans.push_back(vals[it]);
      it = nexts[it];
    }
    return ans;
  }
};

void Solver() {  //
  int m;
  scanf("%d", &m);
  vector<pair<int, int>> tickets;
  tickets.resize(m);

  int maxN = 0;
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    tickets[i] = {u, v};
    maxN = max(maxN, max(u, v));
  }

  Solution s;
  auto& ans = s.findItinerary(maxN, tickets);
  for (auto v : ans) {
    printf("%d\n", v);
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