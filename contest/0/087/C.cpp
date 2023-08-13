/*************************************************************************
    > File Name: C.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月28日 18:28:48
 ************************************************************************/

// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  map<int, int> keyvalue;

 public:
  bool isPossibleDivide(vector<int>& nums, int k) {
    return isNStraightHand(nums, k);
  }
  bool isNStraightHand(vector<int>& hand, int W) {
    if (hand.size() % W != 0) {
      return false;
    }
    for (int i = 0; i < hand.size(); i++) {
      keyvalue[hand[i]]++;
    }

    auto it = keyvalue.begin();

    while (keyvalue.size() > 0) {
      int first = keyvalue.begin()->first;
      for (int i = 0; i < W; i++, first++) {
        it = keyvalue.find(first);
        if (it == keyvalue.end()) {
          return false;
        }
        it->second--;
        if (it->second == 0) {
          keyvalue.erase(it);
        }
      }
    }

    return true;
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
  int second;
  bool expectAns;

  first = {1, 2, 3, 6, 2, 3, 4, 7, 8};
  second = 3;
  expectAns = 1;
  TEST_SMP2(Solution, isNStraightHand, expectAns, first, second);

  first = {1, 2, 3, 4, 5};
  second = 4;
  expectAns = 0;
  TEST_SMP2(Solution, isNStraightHand, expectAns, first, second);

  return 0;
}
