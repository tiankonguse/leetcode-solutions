// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}

class Solution {
  vector<int> nums;
  ll multiplier;
  ll CheckSum(ll maxVal) {
    // 计算每个数字，乘以 mul 若干次后，不超过 maxVal 的最大操作数
    ll sum = 0;
    for (ll v : nums) {
      while (v * multiplier <= maxVal) {
        v = v * multiplier;
        sum++;
      }
    }
    return sum;
  }

 public:
  vector<int> getFinalStateEnum(vector<int>& nums, ll k, ll multiplier) {
    min_queue<pair<ll, ll>> que;
    int n = nums.size();
    for (ll i = 0; i < n; i++) {
      ll v = nums[i];
      que.push({v, i});
    }
    while (k--) {
      auto [v, i] = que.top();
      que.pop();
      v = v * multiplier;
      que.push({v, i});
    }
    while (!que.empty()) {
      auto [v, i] = que.top();
      que.pop();
      nums[i] = v;
    }
    return nums;
  }
  vector<int> getFinalState(vector<int>& nums_, ll k, ll multiplier) {
    if (multiplier == 1) return nums_;
    this->multiplier = multiplier;
    nums.swap(nums_);
    ll maxVal = *max_element(nums.begin(), nums.end());

    // 计算每个数字，乘以 mul 若干次后，不超过 maxVal 的最大操作数
    ll sum = CheckSum(maxVal);

    if (sum >= k) {
      // k 次操作后，答案不超过 maxVal
      // 数据量不大，直接枚举
      return getFinalStateEnum(nums, k, multiplier);
    } else {
      // k 次操作后，答案超过 maxVal
      // 先操作，进行标准化，从而保持有序性，且最小值乘以 mul 会超过最大值
      for (int& v : nums) {
        while (v * multiplier <= maxVal) {
          v = v * multiplier;
          k--;
        }
      }

      ll n = nums.size();
      vector<pair<ll, ll>> indexs(n);
      for (ll i = 0; i < n; i++) {
        ll v = nums[i];
        indexs[i] = {v, i};
      }
      sort(indexs.begin(), indexs.end());
      ll times = k / n;
      if (times > 0) {
        ll tmp = qpow(multiplier, times, mod);
        for (ll i = 0; i < n; i++) {
          indexs[i].first = (indexs[i].first * tmp) % mod;
        }
      }
      k = k % n;
      for (ll i = 0; i < k; i++) {
        indexs[i].first = (indexs[i].first * multiplier) % mod;
      }
      for (auto [v, i] : indexs) {
        nums[i] = v;
      }
      return nums;
    }
  }
};
