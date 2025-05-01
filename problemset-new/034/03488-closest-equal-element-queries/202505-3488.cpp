
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
  vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
    unordered_map<int, vector<int>> m;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      m[nums[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
      m[nums[i]].push_back(i + n);
    }
    vector<int> ans(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      int q = queries[i];
      int v = nums[q];
      if (m[v].size() == 2) {
        ans[i] = -1;
      } else {
        auto& h = m[v];
        int l = lower_bound(h.begin(), h.end(), q) - h.begin();
        int ans1 = h[l + 1] - h[l];
        int r = lower_bound(h.begin(), h.end(), q + n) - h.begin();
        int ans2 = h[r] - h[r - 1];
        ans[i] = min(ans1, ans2);
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