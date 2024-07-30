// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  int ans;
  vector<ll> sum;
  set<ll> posToZero;

  void Add(int i) { posToZero.insert(i); };

  void Init(const string& s) {
    n = s.size();
    sum.resize(n + 1, 0);

    Add(0);
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';
      sum[i] = sum[i - 1] + v;
      if (v == 0) {
        Add(i);
      }
    }
    Add(n + 1);
  }

  // 如果字符串中 1 的数量 大于或等于 0 的数量的 平方，则认为该字符串是一个 1
  // 显著 的字符串 。
  bool Check(int l, int r) {
    ll n = r - l + 1;
    ll oneNum = sum[r] - sum[l - 1];
    ll zeroNum = n - oneNum;
    return oneNum >= zeroNum * zeroNum;
  };

  void Solver(const int i) {
    // 枚举 0 的个数
    // 0 个 0 特殊计算
    auto ith = posToZero.lower_bound(i);  // 从第 i 位置起的第一个 0
    if (*ith != i) {  // 位置 i 不是 0， 计算 0 个 0 的答案
      ans += *ith - i;
      // printf("no zero: add + %lld\n", *ith - i);
    }
    ith++;  // 指向下一个 0

    ll zeroNum = 0;
    int nextIndex = 0, preIndex = 0;
    auto pre = ith;

    while (ith != posToZero.end()) {
      // printf("i=%d ith=%lld\n", i, *ith);
      // 判断是否因为 0 太多，而需要快速后跳
      while (ith != posToZero.end()) {
        nextIndex = *ith;
        pre = ith;
        pre--;
        preIndex = *pre;
        // printf("i=%d ith=%lld pre=%lld\n", i, nextIndex, preIndex);

        const ll oldOneNum = sum[preIndex] - sum[i - 1];
        const ll oldZeroNum = preIndex - i + 1 - oldOneNum;
        const ll doubleZeroNum = oldZeroNum * oldZeroNum;
        const ll oldMinLen = max(oldOneNum, doubleZeroNum) + oldZeroNum;

        ll oldRight = i + oldMinLen - 1;
        // printf("oldOneNum=%lld oldZeroNum=%lld oldMinLen=%lld oldRight=%lld\n", oldOneNum, oldZeroNum, oldMinLen, oldRight);
        if (oldRight < nextIndex) {  // 最小长度没有超过下个0， 说明找到答案
          // printf("i=%d add=%lld\n", i, nextIndex - oldRight);
          ans += nextIndex - oldRight;
          break;
        }

        ith = posToZero.upper_bound(oldRight);
      }
      if (ith == posToZero.end()) {
        break;
      }

      // zeroNum = (preIndex - i + 1) - (sum[preIndex] - sum[i - 1]);
      ith++;
    }
  }

 public:
  int numberOfSubstrings(const string& s) {
    Init(s);

    ans = 0;
    for (ll i = 1; i <= n; i++) {
      Solver(i);
    }
    return ans;
  }
};