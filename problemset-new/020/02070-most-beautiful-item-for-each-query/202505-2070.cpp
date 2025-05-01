
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
  vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
    int n = items.size();
    sort(items.begin(), items.end());
    vector<pair<int, int>> nums(n);
    nums[0] = {items[0][0], items[0][1]};
    for (int i = 1; i < n; i++) {
      nums[i] = {items[i][0], max(nums[i - 1].second, items[i][1])};
    }
    vector<int> ans(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      pair<int, int> q = {queries[i] + 1, 0};
      auto it = lower_bound(nums.begin(), nums.end(), q);
      if (it == nums.begin()) {
        ans[i] = 0;
      } else {
        it--;
        ans[i] = it->second;
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