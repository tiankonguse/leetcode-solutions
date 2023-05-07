// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll maxSum = 0;
  vector<int> tree;
  vector<ll> sums;
  vector<ll> adds;
  int n;
  int secondLev;
  void DfsMaxSum(int p, ll preSum) {
    sums[p - 1] = preSum + tree[p - 1];
    if (p > secondLev) {
      maxSum = max(maxSum, sums[p - 1]);
      return;
    }
    DfsMaxSum(2 * p, sums[p - 1]);
    DfsMaxSum(2 * p + 1, sums[p - 1]);
  }

 public:
  int minIncrements(int n_, vector<int>& cost) {
    n = n_;
    secondLev = n / 2;
    tree.swap(cost);
    adds.resize(n, 0);
    sums.resize(n, 0);
    DfsMaxSum(1, 0);

    ll ans = 0;
    for (int i = secondLev + 1; i <= n; i++) {
      adds[i - 1] = maxSum - sums[i - 1];
      ans += adds[i - 1];
    }

    for (int i = secondLev; i >= 1; i--) {
      int l = i * 2, r = i * 2 + 1;
      adds[i - 1] = min(adds[l - 1], adds[r - 1]);
      ans -= adds[i - 1];
    }

    return ans;
  }
};