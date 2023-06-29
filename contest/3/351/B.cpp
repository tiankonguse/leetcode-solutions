// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int builtin_popcount(ll num) {
    int ans = 0;
    while (num) {
      if (num % 2) ans++;
      num /= 2;
    }
    return ans;
  }

  bool Check(ll num, int k) {
    if (num <= 0) return false;
    int K = builtin_popcount(num);
    if (K > k) return false;
    if (num < k) return false;
    return true;
  }

 public:
  int makeTheIntegerZero(ll num1, ll num2) {
    int ans = 0;
    while (ans < 64 * 2) {
      ans++;
      ll num = num1 - ans * num2;
      printf("num=%lld ans=%d bit=%d\n", num, ans, builtin_popcount(num));
      ll tmp = num;
      while (tmp) {
        printf("%d", tmp % 2);
        tmp /= 2;
      }
      printf("\n");
      if (Check(num, ans)) {
        return ans;
      }
    }
    return -1;
  }
};