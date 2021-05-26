/*************************************************************************
    > File Name: jump-game-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月18日 19:19:42
    > link: https://leetcode.com/problems/jump-game-ii/
    > No: 45. Jump Game II
    > Contest:
 ************************************************************************/

#include "base.h"

class Solution {
 public:
  int jump(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 0);

    int maxPos = 1;
    for (int i = 0; i < n; i++) {
      while (i + nums[i] >= maxPos && maxPos < n) {
        ans[maxPos] = ans[i] + 1;
        maxPos++;
      }
    }
    return ans.back();
  }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION jump

  int first;
  int second;
  int expectAns;

  first = 113;
  second = 1;
  expectAns = -1;
  // TEST_SMP1(CLASS, FUNCTION, expectAns, first);
  // TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

  return 0;
}
