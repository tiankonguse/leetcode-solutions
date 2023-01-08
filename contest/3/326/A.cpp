// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countDigits(int num) {
    std::string str = to_string(num);
    int ans = 0;
    for (auto c : str) {
      int v = c - '0';
      if (c == 0) continue;
      if (num % v == 0) {
        ans++;
      }
    }
    return ans;
  }
};