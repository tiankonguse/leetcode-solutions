// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
class Solution {
 public:
  ll minimumMoves(const vector<int>& nums, const int K, const int maxChanges) {
    int n = nums.size();
    vector<ll> sums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      sums[i] = sums[i - 1] + nums[i - 1];
    }
    vector<ll> sumsums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      if (nums[i - 1] == 0) {
        sumsums[i] = sumsums[i - 1];
      } else {
        sumsums[i] = sumsums[i - 1] + i;
      }
    }

    auto Change = [&](ll a, ll b, ll c) -> ll {
      ll ans = 0;
      ll k = K;
      ll num = maxChanges;

      if (b == 1) {
        k--;
      }
      if (k && a) {
        ans++;
        k--;
      }
      if (k && c) {
        ans++;
        k--;
      }
      if (k <= num) {  // 有答案
        ans += k * 2;
        return ans;
      } else {
        return -1;
      }
    };
    auto CalAns = [&](ll p, ll k, int l) -> ll {
      // printf("p=%lld k=%lld l=%lld\n", p, k, l);
      ll preSum = sums[l - 1];
      ll afterSum = preSum + k;
      auto it = lower_bound(sums.begin(), sums.end(), afterSum);
      if (it == sums.end()) {
        return INFL;  // 1 不够，没有答案
      }

      int r = it - sums.begin();  // 下标是是正确的，且是从1开始的，不需要修正

      if (r <= p) {  // 都在前面
        return p * k - (sumsums[r] - sumsums[l - 1]);
      } else if (p <= l) {  // 都在后面
        return (sumsums[r] - sumsums[l - 1]) - p * k;
      } else {  // 在中间
        ll leftK = sums[p] - sums[l - 1];
        ll rightK = sums[r] - sums[p - 1];
        ll leftAns = p * leftK - (sumsums[p] - sumsums[l - 1]);
        ll rightAns = (sumsums[r] - sumsums[p - 1]) - p * rightK;
        return leftAns + rightAns;
      }
    };
    ll ans = max(sumsums[n], INFL);  //都移动
    for (int i = 1; i <= n; i++) {   // 枚举 index
      // 优先判断只使用 maxChanges 是否可以找到答案
      ll a = 0, b = 0, c = 0;
      if (i != 1) a = nums[i - 2];
      b = nums[i - 1];
      if (i != n) c = nums[i];

      ll changeAns = Change(a, b, c);
      if (changeAns != -1) {
        // printf("i=%d a=%lld b=%lld c=%lld changeAns=%lld\n", i, a, b, c,
        //        changeAns);
        ans = min(ans, changeAns);
        continue;
      }

      // 需要从其他地方交换
      const ll k = K - maxChanges;  // maxChanges * 2, 剩余 k 个 1 需要选择

      // 接下来需要进行三分
      ll l = 1, r = n;
      while (l < r) {  //[l, r]
        // printf("i=%d l=%lld r=%lld\n", i, l, r);
        if (l + 3 > r) {  // 小于3，不够三分
          ll ansL = CalAns(i, k, l);
          ll ansR = CalAns(i, k, r);
          if (ansL < ansR) {
            r--;
          } else {
            l++;
          }
        } else {
          ll midl = l + (r - l) / 3;
          ll midr = r - (r - l) / 3;
          ll ansMidL = CalAns(i, k, midl);
          ll ansMidR = CalAns(i, k, midr);
          if (ansMidL > ansMidR) {  // 左边大
            l = midl;
          } else {
            r = midr;
          }
        }
      }
      ll ansTmp = CalAns(i, k, l) + maxChanges * 2;
      // printf("i=%d k=%lld l=%lld r=%lld ansTmp=%lld\n", i, k, l, r, ansTmp);
      ans = min(ans, ansTmp);
    }

    return ans;
  }
};