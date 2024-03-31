// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int sumOfTheDigitsOfHarshadNumber(const int x) {
    int ans = 0;
    int X = x;
    while (X) {
      ans += X % 10;
      X /= 10;
    }
    if (x % ans != 0) return -1;
    return ans;
  }
};