
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
  int maxCapacity(vector<int>& costs, vector<int>& capacitys, int budget) {
    int n = costs.size();
    vector<pair<int, int>> nums;
    nums.reserve(n);
    int maxCost = 0;
    for (int i = 0; i < n; i++) {
      nums.push_back({costs[i], capacitys[i]});
      maxCost = max(maxCost, costs[i]);
    }
    sort(nums.begin(), nums.end());
    vector<int> preMax(maxCost + 1, 0);
    int nowMaxCost = 0;
    int ans = 0;
    for (auto [cost, capacity] : nums) {
      // 选择 cost 一个
      if (cost < budget) {
        int leftCost = min(budget - cost - 1, nowMaxCost);
        MyPrintf("cost=%d capacity=%d preMax[%d]=%d ans=%d\n", cost, capacity, leftCost, preMax[leftCost],
                 capacity + preMax[leftCost]);
        ans = max(ans, capacity + preMax[leftCost]);
      }
      while (nowMaxCost < cost) {
        preMax[nowMaxCost + 1] = preMax[nowMaxCost];
        nowMaxCost++;
      }
      preMax[nowMaxCost] = max(preMax[nowMaxCost], capacity);
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