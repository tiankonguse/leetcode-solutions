// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  int Sum(string& s, int l, int r) {
    int sum = 0;
    while (l < r) {
      sum += s[l] - '0';
      l++;
    }
    // printf("s=%s, l=%d r=%d n=%d sum=%d\n", s.c_str(), l, r, s.size(), sum);
    return sum;
  }
  bool Check(int x) {
    string s = to_string(x);
    int n = s.length();
    if (n % 2 == 1) {
      return false;
    }
    return Sum(s, 0, n / 2) == Sum(s, n / 2, n);
  }

 public:
  int countSymmetricIntegers(int low, int high) {
    int ans = 0;
    while (low <= high) {
      if (Check(low)) {
        ans++;
      }
      low++;
    }
    return ans;
  }
};
