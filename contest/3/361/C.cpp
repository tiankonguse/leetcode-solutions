// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

vector<int> vec;
typedef long long ll;
class Solution {
  int preNumCallback(int i) {
    if (i == 0) {
      return vec[i] + 1;
    } else {
      return vec[i] - vec[i - 1];
    }
  }

 public:
  ll countInterestingSubarrays(vector<int>& nums, int mod, int k) {
    ll n = nums.size();
    vec.clear();
    vec.reserve(n);
    for (int i = 0; i < n; i++) {
      if (nums[i] % mod == k) {
        vec.push_back(i);
      }
    }
    ll m = vec.size();
    ll ans = 0;
    if (m == 0) {
      if (k != 0) return 0;
      n++;
      return n * (n - 1) / 2;
    }

    for (ll i = 0; i < mod && i < m; i++) {
      ll sum = 0;
      ll K = k;
      if (K == 0) {
        K = mod;
      }
      for (ll j = i + K - 1; j < m; j += mod) {
        // 倒数第 k 个前面有多少个可以选择
        sum += preNumCallback(j - K + 1);
        ll num = 0;
        if (j == m - 1) {
          num = n - vec[j];
        } else {
          num = vec[j + 1] - vec[j];
        }
        ans += sum * num;
      }
    }
    // printf("ans=%lld\n", ans);
    if (k == 0) {  // 夹缝中也合法
      for (ll i = 0; i < m; i++) {
        ll num = preNumCallback(i);
        ans += num * (num - 1) / 2;
      }

      // [vec[m-1], n]
      ll num = n - vec.back();
      ans += num * (num - 1) / 2;
      // printf("ans=%lld\n", ans);
    }

    return ans;
  }
};