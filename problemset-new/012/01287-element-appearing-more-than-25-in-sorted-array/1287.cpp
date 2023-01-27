// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findSpecialInteger(vector<int>& arr) {
    int num = 0;
    int pre = -1;
    int ansNum = 0;
    int ansVal = -1;
    for (auto v : arr) {
      if (v != pre) {
        pre = v;
        num = 0;
      }
      num++;
      if (num > ansNum) {
        ansNum = num;
        ansVal = pre;
      }
    }
    return ansVal;
  }
};