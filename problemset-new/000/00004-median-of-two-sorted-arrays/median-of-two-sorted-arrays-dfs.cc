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
  int dfs(vector<int>& v1, pair<int, int> p1, vector<int>& v2,
          pair<int, int> p2, int k) {
    // printf("v1[%d] {%d,%d} v2[%d]{%d,%d} k=%d\n", v1[p1.first], p1.first,
    //        p1.second, v2[p2.first], p2.first, p2.second, k);
    if (p1.first == p1.second) {
      return v2[p2.first + k - 1];
    }
    if (p2.first == p2.second) {
      return v1[p1.first + k - 1];
    }

    int mid1 = (p1.first + p1.second) / 2;
    int mid2 = (p2.first + p2.second) / 2;

    if (v1[mid1] > v2[mid2]) {
      return dfs(v2, p2, v1, p1, k);
    }

    int len1 = mid1 - p1.first + 1;
    int len2 = mid2 - p2.first + 1;
    if (len1 + len2 > k) {
      return dfs(v1, p1, v2, {p2.first, mid2}, k);
    } else {
      return dfs(v1, {mid1 + 1, p1.second}, v2, p2, k - len1);
    }
  }

 public:
  double findMedianSortedArrays(vector<int>& v1, vector<int>& v2) {
    int len1 = v1.size();
    int len2 = v2.size();
    int allNum = len1 + len2;
    if (allNum % 2 == 0) {
      double a = dfs(v1, {0, len1}, v2, {0, len2}, allNum / 2);
      double b = dfs(v1, {0, len1}, v2, {0, len2}, allNum / 2 + 1);
      // printf("a=%lf b=%lf\n", a, b);
      return (a + b) / 2.0;
    } else {
      return dfs(v1, {0, len1}, v2, {0, len2}, allNum / 2 + 1);
    }
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
#define FUNCTION findMedianSortedArrays

  TEST_SMP2(CLASS, FUNCTION, 2.0, vector<int>({1, 3}), vector<int>({2}));

  TEST_SMP2(CLASS, FUNCTION, 2.5, vector<int>({1, 2}), vector<int>({3, 4}));
  TEST_SMP2(CLASS, FUNCTION, 0.0, vector<int>({0, 0}), vector<int>({0, 0}));
  TEST_SMP2(CLASS, FUNCTION, 1.0, vector<int>({}), vector<int>({1}));
  TEST_SMP2(CLASS, FUNCTION, 2.0, vector<int>({2}), vector<int>({}));

  return 0;
}
