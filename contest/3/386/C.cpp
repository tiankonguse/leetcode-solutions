// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int earliestSecondToMarkIndices(const vector<int>& nums,
                                  const vector<int>& changeIndices) {
    const int n = nums.size();
    const int m = changeIndices.size();

    // 剪枝，操作数必须大于够
    // ll sum = n;
    // for (auto v : nums) {
    //   sum += v;
    //   if (sum > m) {
    //     return -1;
    //   }
    // }

    auto Check = [&](const int mid) -> bool {
      unordered_set<int> flag;
      ll sum = 0;
      for (int i = mid - 1; i >= 0; i--) {
        int v = changeIndices[i] - 1;
        if (flag.count(v) == 0) {
          sum += nums[v];  // 选择标记
          flag.insert(v);
          continue;
        }

        if (sum > 0) {
          sum--;
        }
      }
      // printf("mid=%d flagsize=%d sum=%lld\n", mid, flag.size(), sum);
      return flag.size() == n && sum == 0;
    };

    int l = 1, r = m + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (r == m + 1) return -1;
    return r;
  }
};