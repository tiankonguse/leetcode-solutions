
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
class Solution {
 public:
  ll weightedSum(vector<int>& parent, vector<int>& nums) {  //
    int n = parent.size();
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++) {
      int p = parent[i];
      tree[p].push_back(i);
    }

    vector<ll> heights(n, 0);
    ll maxHeight = 0;
    auto DfsHeight = [&](auto&& self, int u, ll h) -> void {
      heights[u] = h;
      maxHeight = max(maxHeight, h);
      for (auto v : tree[u]) {
        self(self, v, h + 1);
      }
    };
    DfsHeight(DfsHeight, 0, 1);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += nums[i] * (maxHeight - heights[i] + 1);
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