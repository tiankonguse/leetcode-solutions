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
  string convert(string s, int nRows) {
    if (nRows == 1) {
      return s;
    }

    int length = s.length();
    string ans;
    ans.resize(length);

    int step = 2 * nRows - 2;
    int K = step;
    int line = 1;
    int next;

    int start = 0;

    // first line
    for (int i = line; i <= length; i += step) {
      ans[start++] = s[i - 1];
    }

    // middle line
    for (line++, K -= 2; line < nRows; line++, K -= 2) {
      for (int i = line; i <= length; i += step) {
        ans[start++] = s[i - 1];

        if (i + K <= length) {
          ans[start++] = s[i + K - 1];
        }
      }
    }

    // last line
    for (int i = line; i <= length; i += step) {
      ans[start++] = s[i - 1];
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
#define FUNCTION convert

  TEST_SMP2(CLASS, FUNCTION, string("LCIRETOESIIGEDHN"),
            string("LEETCODEISHIRING"), 3);
  TEST_SMP2(CLASS, FUNCTION, string("LDREOEIIECIHNTSG"),
            string("LEETCODEISHIRING"), 4);

  return 0;
}
