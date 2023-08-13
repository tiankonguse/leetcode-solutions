/*****************
********************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:44
 ************************************************************************/

// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int longestMountain(vector<int>& A) {
    if (A.size() < 3) {
      return 0;
    }
    int first = 0;
    int mid = -1;
    int state = 0;  // 0:up, 1:down
    int ans = 0, tmpAns = 0;
    for (int i = 1; i < A.size(); i++) {
      if (state == 0) {
        if (A[i] > A[i - 1]) {
          mid = i;
        } else if (A[i] < A[i - 1]) {
          if (mid == -1) {
            first = i;
            mid = -1;
          } else {
            state = 1;
            ans = max(ans, i - first + 1);
          }
        } else {
          first = i;
          mid = -1;
        }
      } else {
        if (A[i] < A[i - 1]) {
          ans = max(ans, i - first + 1);
        } else if (A[i] > A[i - 1]) {
          state = 0;
          first = i - 1;
          mid = i;
        } else {
          state = 0;
          first = i;
          mid = -1;
        }
      }
    }
    return ans;
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

  first = {2, 1, 4, 7, 3, 2, 5};
  expectAns = 5;
  TEST_SMP1(Solution, longestMountain, expectAns, first);

  first = {2, 2, 2};
  expectAns = 0;
  TEST_SMP1(Solution, longestMountain, expectAns, first);

  return 0;
}
