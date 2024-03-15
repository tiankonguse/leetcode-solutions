// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findBestValue(vector<int>& arr, int target) {
    int n = arr.size();

    sort(arr.begin(), arr.end());

    vector<ll> preSum = {0};
    ll sum = 0;
    preSum.reserve(n + 1);
    for (auto v : arr) {
      sum += v;
      preSum.push_back(sum);
    }

    ll ans = 0;
    ll dis = target;
    for (ll v = 0; v <= target; v++) {
      ll k = upper_bound(arr.begin(), arr.end(), v) - arr.begin();
      ll tmp = abs(preSum[k] + (n - k) * v - target);

      if (tmp < dis) {
        dis = tmp;
        ans = v;
      }
    }
    return ans;
  }
};