
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
  vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    vector<int> pre(n, 0);
    for (int i = 0; i < n; i++) {
      pre[i] = i;
    }
    for (int i = 1; i < n; i++) {
      if (abs(nums[i] - nums[i - 1]) <= maxDiff) {
        pre[i] = pre[i - 1];
      }
    }
    vector<bool> ans(queries.size(), false);
    for (int i = 0; i < queries.size(); i++) {
      int l = queries[i][0], r = queries[i][1];
      if (pre[r] == pre[l]) {
        ans[i] = true;
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