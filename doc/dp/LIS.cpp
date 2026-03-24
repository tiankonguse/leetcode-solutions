#include "base.h"

// LIS：Longest Increasing Subsequence 最长递增子序列
// 可以解决以下题型：
// 任意修改一个值，使数组有序。 未修改的就是 LIS
// 删除任意一个值，使数组有序。 未删除的就是 LIS

template <typename T>
int Lis(vector<T>& a) {
  vector<T> dp;
  for (auto x : a) {
    auto it = upper_bound(dp.begin(), dp.end(), x);
    if (it == dp.end()) {
      dp.push_back(x);
    } else {
      *it = x;
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
