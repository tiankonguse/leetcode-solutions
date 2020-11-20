/*************************************************************************
    > File Name: move-zeroes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 02:41:23 2019
 ************************************************************************/

#include "base.h"

class Solution {
 public:
  vector<int> moveZeroes(vector<int>& nums) {
    int left = 0, right = 0;
    for (; right < nums.size(); right++) {
      if (nums[right] == 0) {
        continue;
      }
      nums[left] = nums[right];
      if (left != right) {
        nums[right] = 0;
      }
      left++;
    }
    return nums;
  }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
  TEST_SMP1(Solution, moveZeroes, vector<int>({1, 3, 12, 0, 0}),
            vector<int>({0, 1, 0, 3, 12}));

  return 0;
}
