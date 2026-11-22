
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

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  vector<ll> earliestActivationTimes(int n, vector<vector<int>>& edges, vector<int>& requiredSignals) {
    vector<ll> ans(n, -1);
    vector<int> inDegree(n, 0);
    vector<vector<pair<int, ll>>> g(n);
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1];
      ll delay = edge[2];
      g[u].push_back({v, delay});
    }
    requiredSignals[0] = 1;
    min_queue<pair<ll, int>> que;
    que.push({0, 0});
    ans[0] = 0;
    while (!que.empty()) {
      auto [t, u] = que.top();
      que.pop();
      inDegree[u]++;
      if (inDegree[u] != requiredSignals[u]) continue;
      ans[u] = t;
      for (auto [v, delay] : g[u]) {
        que.push({t + delay, v});
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif