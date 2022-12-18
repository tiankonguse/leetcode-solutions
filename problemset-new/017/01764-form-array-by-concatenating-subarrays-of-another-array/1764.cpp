// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  bool CheckPos(const vector<int>& group, const int l) {
    const int r = nums.size();
    const int m = group.size();
    for (int j = 0; j < m; j++) {
      if (l + j >= r) {
        return false;
      }
      if (group[j] != nums[l + j]) {
        return false;
      }
    }
    return true;
  }
  bool CheckLoop(const vector<int>& group, int& l) {
    const int r = nums.size();
    const int m = group.size();
    for (int i = l; i < r; i++) {
      if (CheckPos(group, i)) {
        // printf("group size=%d l=%d, match i=%d new l = %d\n", m, l, i, i + m);
        l = i + m;
        return true;
      }
    }
    return false;
  }

 public:
  bool canChoose(vector<vector<int>>& groups, vector<int>& nums_) {
    nums.swap(nums_);
    int l = 0;
    for (const vector<int>& group : groups) {
      if (!CheckLoop(group, l)) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  printf("hello \n");
  //   bool ans = false;
  //   vector<vector<int>> groups = {{1, 2, 3}, {3, 4}};
  //   vector<int> nums = {7, 7, 1, 2, 3, 4, 7, 7};
  //   TEST_SMP2(Solution, canChoose, ans, groups, nums);

  bool ans = false;
  vector<vector<int>> groups = {{-5, 0}};
  vector<int> nums = {2, 0, -2, 5, -1, 2, 4, 3, 4, -5, -5};
  TEST_SMP2(Solution, canChoose, ans, groups, nums);

  return 0;
}
