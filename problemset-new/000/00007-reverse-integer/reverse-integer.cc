/*************************************************************************
  > File Name: median-of-two-sorted-arrays.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
  > Created Time: 2015年05月19日 20:49:56
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "base.h"

class Solution {
 public:
  int reverse(int x) {
    long long X = x;
    int sign = 1;
    if (X < 0) {
      sign = -1;
      X = -X;
    }

    long long ans = 0;
    while (X > 0) {
      ans = ans * 10 + (X % 10);
      X = X / 10;
    }
    ans = ans * sign;

    if (ans < INT_MIN || ans > INT_MAX) {
      return 0;
    }

    return ans;
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
#define FUNCTION reverse

  TEST_SMP1(CLASS, FUNCTION, 321, 123);
  TEST_SMP1(CLASS, FUNCTION, -123, -321);
  TEST_SMP1(CLASS, FUNCTION, 21, 120);
  TEST_SMP1(CLASS, FUNCTION, 0, INT_MIN);
  TEST_SMP1(CLASS, FUNCTION, 0, 1534236469);

  return 0;
}
