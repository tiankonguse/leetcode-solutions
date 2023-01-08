// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll GetSum(int n, ll value) {
    if (value >= n) {
      ll firstVal = value - n + 1;
      return (firstVal + value) * n / 2;
    } else {
      return (value + 1) * value / 2 + (n - value);
    }
  }
  bool check(ll n, ll index, ll maxSum, ll value) {
    ll sum = -value;

    // sum[0, index]
    sum += GetSum(index + 1, value);

    // sum[index, n-1]
    sum += GetSum(n - index, value);

    if (sum > maxSum) {
      return false;
    } else {
      return true;
    }
  }

 public:
  int maxValue(int n, int index, int maxSum) {
    ll low = 1, high = maxSum + 1;
    while (low < high) {
      ll mid = (low + high + 1) / 2;
      if (check(n, index, maxSum, mid)) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    return low;
  }
};