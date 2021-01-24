#include "base.h"

// lower_bound 大于等于
// upper_bound 大于

const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
 public:
  vector<int> mostCompetitive(vector<int>& nums, int k) {
    int n = nums.size();
    if (k == n) {
      return nums;
    }
    vector<int> ans;

    // 前面 [0, n-k+1) 范围，保持单点递增
    for (int i = 0; i < n - k + 1; i++) {
      while (!ans.empty() && ans.back() > nums[i]) {
        ans.pop_back();
      }
      ans.push_back(nums[i]);
    }

    // 后面 [n-k+1 ,n) 需要满足栈的大小不小于 k
    for (int i = n - k + 1, left = k - 1; i < n; i++) {
      while (ans.size() + n - i > k && ans.back() > nums[i]) {
        ans.pop_back();
      }
      ans.push_back(nums[i]);
    }
    ans.resize(k);

    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, mostCompetitive, vector<int>({2, 6}),
            vector<int>({3, 5, 2, 6}), 2);
  TEST_SMP2(Solution, mostCompetitive, vector<int>({2, 3, 3, 4}),
            vector<int>({2, 4, 3, 3, 5, 4, 9, 6}), 4);
  return 0;
}
