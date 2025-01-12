
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  vector<vector<pair<int, int>>> g;
  int n;
  vector<int> flag;
  vector<int> sta;
  int index = 0;
  bool Check(int W) {
    index++;

    sta.push_back(0);
    flag[0] = index;

    while (!sta.empty()) {
      auto u = sta.back();
      sta.pop_back();
      for (auto [v, w] : g[u]) {
        if (w > W) continue;
        if (flag[v] == index) continue;
        sta.push_back(v);
        flag[v] = index;
      }
    }
    for (int i = 0; i < n; i++) {
      if (flag[i] != index) return false;
    }
    return true;
  }

 public:
  int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {  //
    this->n = n;
    g.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1], w = e[2];
      g[v].push_back({u, w});
    }
    flag.resize(n, 0);
    sta.reserve(n);
    ll l = 0, r = INT_MAX;
    while (l < r) {
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r == INT_MAX ? -1 : r;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif