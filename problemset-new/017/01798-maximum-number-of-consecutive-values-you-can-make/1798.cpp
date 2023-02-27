// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int getMaximumConsecutive(vector<int>& coins) {
    sort(coins.begin(), coins.end());
    int offset = 0;

    for (auto v : coins) {
      if (offset + 1 >= v) {
        offset += v;
      } else {
        break;
      }
    }
    return offset + 1;
  }
};
