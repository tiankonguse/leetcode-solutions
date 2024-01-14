// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxFrequencyElements(vector<int>& nums) {
    map<int, int> h;
    for (auto v : nums) {
      h[v]++;
    }

    int ansSum = 0;
    int ansNum = 0;

    for (auto [k, v] : h) {
      if (v == ansNum) {
        ansSum += v;
      } else if (v > ansNum) {
        ansSum = v;
        ansNum = v;
      }
    }
    return ansSum;
  }
};