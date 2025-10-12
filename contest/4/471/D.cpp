
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
const int N = 1e5 + 10;
class Solution {
  vector<vector<int>> g;
  vector<int> nums;
  vector<ll> valFlag;
  ll ans = 0;
  void Init() {
    for (auto& v : nums) {
      int sq = sqrt(v) + 1;
      for (int i = 2; i <= sq; i++) {
        while (v % (i * i) == 0) {
          v /= (i * i);
        }
      }
    }
  }
  void Dfs(int u, int pre) {
    ans += valFlag[nums[u]];
    valFlag[nums[u]]++;
    for (auto v : g[u]) {
      if (v == pre) continue;
      Dfs(v, u);
    }
    valFlag[nums[u]]--;
  }

 public:
  long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums_) {
    nums.swap(nums_);
    Init();
    g.resize(n);
    for (auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    valFlag.resize(N, 0);
    Dfs(0, -1);
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