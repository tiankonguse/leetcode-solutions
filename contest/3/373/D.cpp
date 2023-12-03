// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int FixK(int k) {
    map<int, int> h;
    for (int i = 2; i <= k; i++) {
      while (k % i == 0) {
        h[i]++;
        k /= i;
      }
    }

    int K = 1;
    for (auto [k, v] : h) {
      if (v % 2 == 1) {
        v++;  // 补齐为偶数
      }
      v /= 2;
      while (v--) {
        K *= k;
      }
    }
    return K;
  }

 public:
  ll beautifulSubstrings(const string& s, int K) {
    int n = s.size();
    set<char> h = {'a', 'e', 'i', 'o', 'u'};

    vector<int> nums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      nums[i] = nums[i - 1];
      if (h.count(s[i - 1])) {
        nums[i]++;
      } else {
        nums[i]--;
      }
    }

    K = FixK(K);
    printf("k=%d\n", K);
    ll ans = 0;
    // 2*K 偏移量进行分组
    unordered_map<int, ll> stat;

    for (int i = 0; i < 2 * K; i++) {  // 枚举[0, 2K)
      stat.clear();
      for (int j = i + 2 * K; j <= n; j += 2 * K) {  // (0,2K, 4K, 8K, ...]
        stat[nums[j] - nums[i]]++;
      }
      for (auto [k, v] : stat) {  // 最多 2*K 个
        printf("i=%d stat: k=%d v=%lld\n", i, k, v);
        if (k == 0) {
          v++;
          ans += v * (v - 1) / 2;
        } else {
          ans += v * (v - 1) / 2;
        }
      }
    }

    return ans;
  }
};/*  */