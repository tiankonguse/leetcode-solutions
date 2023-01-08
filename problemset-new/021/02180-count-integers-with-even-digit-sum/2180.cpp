// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
  int Check(int num) {
    int ans = 0;
    // printf("num=%d ", num);
    while (num > 0) {
      ans += num % 10;
      num /= 10;
    }
    // printf("ans=%d\n", ans);
    return ans % 2 == 0;
  }

 public:
  int countEven(int num) {
    int ans = 0;
    while (num > 0) {
      ans += Check(num);
      num--;
    }
    return ans;
  }
};