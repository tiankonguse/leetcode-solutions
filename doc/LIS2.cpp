#include "base.h"

// LIS：Longest Increasing Subsequence 最长递增子序列
// 可以解决以下题型：
// 任意修改一个值，使数组有序。 未修改的就是 LIS
// 删除任意一个值，使数组有序。 未删除的就是 LIS

int Lis2(vector<pair<int, int>>& nums) {
  sort(nums.begin(), nums.end(), [](auto& a, auto& b) {
    if (a[0] == b[0]) {
      return a[1] > b[1];
    } else {
      return a[0] < b[0];
    }
  });
  vector<int> dp;
  for (const auto& v : nums) {
    const int y = v.second;
    auto it = upper_bound(dp.begin(), dp.end(), y);
    if (it == dp.end()) {
      dp.push_back(y);
    } else {
      *it = y;
    }
  }
  return dp.size();
}

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
