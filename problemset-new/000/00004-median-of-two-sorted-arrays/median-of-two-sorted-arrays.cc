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
  int find(vector<int>& first, vector<int>& second, int k) {
    int firstPoint = 0;
    int secondPoint = 0;
    int firstSize = first.size();
    int secondSize = second.size();
    k++;  // begin 1

    int ans = 0;
    while (k > 0) {
      int firstmid = (firstPoint + firstSize) / 2;
      int firstLen = firstmid - firstPoint + 1;
      int secondmid = (secondPoint + secondSize) / 2;
      int secondLen = secondmid - secondPoint + 1;

      if (firstPoint < firstSize && secondPoint < secondSize) {
        if (first[firstmid] < second[secondmid]) {
          if (firstLen + secondLen > k) {
            secondSize = secondmid;
          } else {
            k -= firstLen;
            firstPoint = firstmid + 1;
          }
        } else {
          if (firstLen + secondLen > k) {
            firstSize = firstmid;
          } else {
            k -= secondLen;
            secondPoint = secondmid + 1;
          }
        }
      } else if (firstPoint < firstSize) {
        if (firstLen > k) {
          firstSize = firstmid;
        } else if (firstLen < k) {
          k -= firstLen;
          firstPoint = firstmid + 1;
        } else {
          return first[firstmid];
        }
      } else if (secondPoint < secondSize) {
        if (secondLen > k) {
          secondSize = secondmid;
        } else if (secondLen < k) {
          k -= secondLen;
          secondPoint = secondmid + 1;
        } else {
          return second[secondmid];
        }
      }
    }
    return ans;
  }

 public:
  double findMedianSortedArrays(vector<int>& first, vector<int>& second) {
    int allNum = first.size() + second.size();
    if (allNum % 2 == 0) {
      double a = find(first, second, allNum / 2);
      double b = find(first, second, allNum / 2 - 1);
      return (a + b) / 2.0;
    } else {
      return find(first, second, allNum / 2);
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
