// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countAsterisks(string s) {
    int ans = 0;
    int flag = 0;
    for (auto c : s) {
      if (c == '|') {
        flag = 1 - flag;
      } else if (c == '*') {
        if (flag == 0) ans++;
      }
    }
    return ans;
  }
};