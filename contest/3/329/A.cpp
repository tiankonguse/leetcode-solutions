// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int alternateDigitSum(int n) {
    int len = to_string(n).size();
    int ans = 0;
    while (n) {
      if (len % 2 == 1) {
        ans += n % 10;
      } else {
        ans -= n % 10;
      }
      n = n / 10;
      len--;
    }
    return ans;
  }
};