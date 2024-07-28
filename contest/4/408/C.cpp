// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSubstrings(const string& s) {
    int n = s.size();
    vector<ll> sum(n + 1, 0);
    map<ll, ll> posToZero;
    vector<ll> zeroBuf;
    zeroBuf.reserve(n + 2);

    auto Add = [&zeroBuf, &posToZero](int i) {
      zeroBuf.push_back(i);
      posToZero[i] = zeroBuf.size() - 1;
    };

    Add(0);
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';
      sum[i] = sum[i - 1] + v;
      if (v == 0) {
        Add(i);
      }
    }
    Add(n + 1);

    int ans = 0;
    for (ll i = 1; i <= n; i++) {
      // 枚举 0 的个数
      // 0 个 0 特殊计算
      auto ith = posToZero.lower_bound(i);  // 从第 i 位置起的第一个 0
      ll firstZeroPosInAll = ith->first;
      ll firstZeroPosInZero = ith->second;         // 第一个 0 在 zero 数组中的位置

      if(firstZeroPosInAll != i){ // 存在没有 0 的情况，特殊计算
        ans += firstZeroPosInAll - i;
      }

      for (ll j = 1; firstZeroPosInZero + j < zeroBuf.size(); j++) {
        if (firstZeroPosInZero + j > zeroBuf.size()) break;  // j 个 0 的位置比 n+1 之外
        if (i + j * j > n) break;
        int l = zeroBuf[firstZeroPosInZero + j];
        int r = zeroBuf[firstZeroPosInZero + j - 1];  // j 个 0 最长的长度
      }
    }

    return ans;
  }
};