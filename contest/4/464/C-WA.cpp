
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
  vector<int> maxValue(vector<int>& nums) {
    int n = nums.size();
    vector<int> rightMinIndex(n + 1, -1);
    vector<int> leftMaxIndex(n + 1, -1);
    int pre = -1;
    for (int i = 0; i < n; i++) {
      if (pre == -1) {
        pre = i;
      } else {
        if (nums[i] >= nums[pre]) {
          pre = i;
        }
      }
      leftMaxIndex[i] = pre;
    }
    vector<int> sta;
    sta.reserve(n);
    for (int i = n - 1; i >= 0; i--) {
      if (sta.empty()) {
        sta.push_back(i);
      } else {
        if (nums[i] < nums[sta.back()]) {
          sta.push_back(i);
        }
      }
      // 二分找到第一个大于等于 nums[i] 的位置
      int l = 0, r = sta.size();  // [l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        if (nums[sta[mid]] >= nums[i]) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      if (l == sta.size()) {  // 等于最小值
        rightMinIndex[i] = i;
      } else {
        rightMinIndex[i] = sta[l];
      }
    }
    vector<int> ans(n);
    for(int i=0;i<n;i++){
      int rightIndex = rightMinIndex[i];
      int leftIndex = leftMaxIndex[rightIndex];
      ans[i] = nums[leftIndex];
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