// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSteps(int num) {
    int ans = 0;
    while (num) {
      if (num % 2 == 0) {
        num /= 2;
      } else {
        num--;
      }
      ans++;
    }
    return ans;
  }
};
