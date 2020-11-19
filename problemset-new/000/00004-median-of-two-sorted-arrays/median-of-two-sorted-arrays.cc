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
  int getMaxEdge(int l, int r, string& s) {
    int ans = 0;
    while (l >= 0 && r < s.length() && s[l] == s[r]) {
      ans++;
      l--, r++;
    }
    return ans;
  }

  int maxl = 0, maxr = 0, maxAns = 0;

  void update(int d, int l, int r) {
    int tmpAns = 2 * d;
    if (l == r) {
      tmpAns--;
    }
    if (tmpAns > maxAns) {
      maxl = l - (d - 1);
      maxr = r + (d + 1);
      maxAns = tmpAns;
    }
  }

 public:
  string longestPalindrome(string s) {
    for (int i = 0; i < s.length(); i++) {
      int d = getMaxEdge(i, i, s);
      update(d, i, i);
    }

    for (int i = 0; i < s.length() - 1; i++) {
      int d = getMaxEdge(i, i + 1, s);
      update(d, i, i + 1);
    }

    return s.substr(maxl, maxAns);
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
#define FUNCTION longestPalindrome

  TEST_SMP1(CLASS, FUNCTION, string("bab"), string("babad"));
  TEST_SMP1(CLASS, FUNCTION, string("bb"), string("cbbd"));

  return 0;
}
