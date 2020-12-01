/*************************************************************************
  > File Name: remove-duplicates-from-sorted-array.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
  > Created Time: 2015年06月11日 星期四 00时34分49秒
***********************************************************************/

#include "base.h"

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int s = nums.size();
    if (s == 0) {
      return 0;
    }
    int l = 1, r = 1;
    for (; r < s;) {
      if (nums[r] != nums[l - 1]) {
        nums[l++] = nums[r];
      }
      r++;
    }
    return l;
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
  vector<int> first;
  int expectAns;

  first = {1, 1, 2};
  expectAns = 2;
  TEST_SMP1(Solution, removeDuplicates, expectAns, first);

  first = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  expectAns = 5;
  TEST_SMP1(Solution, removeDuplicates, expectAns, first);

  return 0;
}
