
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
  bool CheckUp(vector<int>& nums) {
    int n = nums.size();
    int p = 1;
    while (p < n && nums[p - 1] < nums[p]) {
      p++;
    }
    if (p == n) {
      return true;  // 严格升序
    }
    for (int i = p + 1; i < n; i++) {
      if (nums[i - 1] > nums[i]) {
        return false;
      }
    }
    if (nums.back() < nums.front()) {
      return true;  // 循环升序
    }
    return false;
  }
  bool CheckDown(vector<int>& nums) {
    std::reverse(nums.begin(), nums.end());
    bool res = CheckUp(nums);
    std::reverse(nums.begin(), nums.end());
    return res;
  }

  int FindUpBound(vector<int>& nums) {
    int n = nums.size();
    int p = 1;
    while (p < n && nums[p - 1] < nums[p]) {
      p++;
    }
    return p;
  }
  int FindDownBound(vector<int>& nums) {
    int n = nums.size();
    int p = 1;
    while (p < n && nums[p - 1] > nums[p]) {
      p++;
    }
    return p;
  }

 public:
  int minOperations(vector<int>& nums) {  //
    int n = nums.size();
    if (n == 1) return 0;
    if (CheckUp(nums)) {
      int p = FindUpBound(nums);
      if (p == n) {
        return 0;
      }
      int ans = n + 1;
      ans = min(ans, p);            // 直接左旋
      ans = min(ans, (n - p) + 2);  // 先反转，再左旋，再反转
      return ans;
    } else if (CheckDown(nums)) {
      int p = FindDownBound(nums);
      if (p == n) {
        return 1;
      }
      int ans = n + 1;
      ans = min(ans, p + 1);        // 先左旋，再反转
      ans = min(ans, (n - p) + 1);  // 先反转，再左旋
      return ans;
    }
    return -1;
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