// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSubstrings(const string& s) {
    int n = s.size();
    vector<ll> sum(n + 1, 0);
    set<ll> posToZero;

    auto Add = [&posToZero](int i) { posToZero.insert(i); };

    Add(0);
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';
      sum[i] = sum[i - 1] + v;
      if (v == 0) {
        Add(i);
      }
    }
    Add(n + 1);

    // 如果字符串中 1 的数量 大于或等于 0 的数量的 平方，则认为该字符串是一个 1
    // 显著 的字符串 。
    auto Check = [&sum](int l, int r) {
      ll n = r - l + 1;
      ll oneNum = sum[r] - sum[l - 1];
      ll zeroNum = n - oneNum;
      return oneNum >= zeroNum * zeroNum;
    };

    int ans = 0;
    for (ll i = 1; i <= n; i++) {
      // 枚举 0 的个数
      // 0 个 0 特殊计算
      auto ith = posToZero.lower_bound(i);  // 从第 i 位置起的第一个 0
      ll firstZeroPosInAll = *ith;

      if (firstZeroPosInAll != i) {  // 位置 i 不是 0， 计算 0 个 0 的答案
        ans += firstZeroPosInAll - i;
      }

      auto pre = ith;
      ith++;

      int zeroNum = 0;
      while (ith != posToZero.end()) {
        int preIndex = *pre;
        int nextIndex = *ith;

        if (Check(i, nextIndex - 1)) {  // 取所有的1， 有答案
          if (Check(i, preIndex)) {     // 只取0，不取后缀1
            // [preIndex, nextIndex - 1] 都是答案
            ans += nextIndex - preIndex;
          } else {  //
            ll oneNum = sum[preIndex] - sum[i - 1];
            ll zeroNum = preIndex - i + 1 - oneNum;
            ll use = zeroNum * zeroNum - oneNum;
            ans += nextIndex - preIndex - use;
          }
        }

        pre = ith;
        ith++;
      }
    }

    return ans;
  }
};