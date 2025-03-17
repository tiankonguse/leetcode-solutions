/*
这道题怎么做，请给出思路。

给你两个正整数 l 和 r 。如果正整数每一位上的数字的乘积可以被这些数字之和整除，则认为该整数是一个 美丽整数 。
统计并返回 l 和 r 之间（包括 l 和 r ）的 美丽整数 的数目。
r <= 10^9
*/

#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const int maxBit = 10;
const int maxSum = 91;
const int max2 = 9;
const int max3 = 5;
const int max5 = 3;
const int max7 = 3;
const int isZero = 2;
ll dpBound[maxBit][maxSum][max2][max3][max5][max7];
ll dpFull[maxBit][maxSum][max2][max3][max5][max7];
ll dpZero[maxBit];
class Solution {
  ll Pow(ll v, int n) {
    if (n < 0) return 1;
    ll ret = 1;
    while (n) {
      if (n & 1) ret *= v;
      v *= v;
      n >>= 1;
    }
    return ret;
  }
  string s;
  int n;
  ll Cal(ll v) {
    if (v == 0) return 1;
    memset(dpBound, 0xFF, sizeof(dpBound));
    memset(dpFull, 0xFF, sizeof(dpFull));
    memset(dpZero, 0xFF, sizeof(dpZero));
    s = to_string(v);
    n = s.length();
    std::reverse(s.begin(), s.end());
    return dfsBound(n - 1, 0, 0, 0, 0, 0);
  }

  bool Check(int sum, int mod2, int mod3, int mod5, int mod7) {
    if (sum == 0) return 1;
    ll mulVal = 1;
    while (mod2) {
      mulVal *= 2;
      mod2--;
    }
    while (mod3) {
      mulVal *= 3;
      mod3--;
    }
    while (mod5) {
      mulVal *= 5;
      mod5--;
    }
    while (mod7) {
      mulVal *= 7;
      mod7--;
    }
    return mulVal % sum == 0;
  }

  void MergeMul(int& V, const int base, int& num, const int maxNum) {
    while (V % base == 0) {
      if (num + 1 == maxNum) {
        break;
      }
      num++;
      V /= base;
    }
  }

  ll dfsBoundZero(int pos) {
    if (pos < 0) return 1;
    ll& ret = dpZero[pos];
    const int maxV = s[pos] - '0';
    if (ret != -1) return ret;
    ret = 0;

    if (maxV == 0) {
      ret += dfsBoundZero(pos - 1);
    } else {
      // [0, maxV) 随意选择
      const int leftBit = pos;  // pos 最低位为 0
      ret += maxV * Pow(10, leftBit);
      ret += dfsBoundZero(pos - 1);
    }

    return ret;
  }

  ll dfsBound(int pos, int sum, int mod2, int mod3, int mod5, int mod7) {
    if (pos < 0) {
      return Check(sum, mod2, mod3, mod5, mod7);
    }
    const int maxV = s[pos] - '0';
    ll& ret = dpBound[pos][sum][mod2][mod3][mod5][mod7];
    // printf("in s=%s pos=%d maxV=%d sum=%d mod2=%d mod3=%d mod5=%d mod7=%d ret=%lld\n", s.data(), pos, maxV, sum,
    // mod2, mod3, mod5, mod7, ret);
    if (ret != -1) return ret;

    ret = 0;

    // 0 特殊处理, 乘以0后，后面的每一位可以是 0~9, 位数后 [0, pos-1] 共 pos 位
    if (maxV > 0) {
      if (sum > 0) {
        const int leftBit = pos;  // pos 最低位为 0
        ret += Pow(10, leftBit);
      } else {
        ret += dfsFull(pos - 1, sum, mod2, mod3, mod5, mod7);
      }
    } else {  // 肯定不是最高位
      ret += dfsBoundZero(pos - 1);
    }

    // [1, maxV-1] 通用化处理, maxV 特殊处理
    for (int v = 1; v <= maxV; v++) {
      int tmp2 = mod2, tmp3 = mod3, tmp5 = mod5, tmp7 = mod7;
      int V = v;
      MergeMul(V, 2, tmp2, max2);
      MergeMul(V, 3, tmp3, max3);
      MergeMul(V, 5, tmp5, max5);
      MergeMul(V, 7, tmp7, max7);
      if (v == maxV) {
        ret += dfsBound(pos - 1, sum + v, tmp2, tmp3, tmp5, tmp7);
      } else {
        ret += dfsFull(pos - 1, sum + v, tmp2, tmp3, tmp5, tmp7);
      }
    }

    // printf("out s=%s pos=%d maxV=%d sum=%d mod2=%d mod3=%d mod5=%d mod7=%d ret=%lld\n", s.data(), pos, maxV, sum,
    // mod2,
    //        mod3, mod5, mod7, ret);
    return ret;
  }
  ll dfsFull(int pos, int sum, int mod2, int mod3, int mod5, int mod7) {
    if (pos < 0) {
      return Check(sum, mod2, mod3, mod5, mod7);
    }
    ll& ret = dpFull[pos][sum][mod2][mod3][mod5][mod7];
    if (ret != -1) return ret;

    ret = 0;
    // 取值 0, sum 为 0 代表高位都是 0，需要递归枚举
    if (sum == 0) {
      ret += dfsFull(pos - 1, sum, mod2, mod3, mod5, mod7);
    } else {
      int leftBit = pos;  // pos 最低位为 0
      ret += Pow(10, leftBit);
    }

    // 取值 1~9
    for (int v = 1; v <= 9; v++) {
      int tmp2 = mod2, tmp3 = mod3, tmp5 = mod5, tmp7 = mod7;
      int V = v;
      MergeMul(V, 2, tmp2, max2);
      MergeMul(V, 3, tmp3, max3);
      MergeMul(V, 5, tmp5, max5);
      MergeMul(V, 7, tmp7, max7);
      ret += dfsFull(pos - 1, sum + v, tmp2, tmp3, tmp5, tmp7);
    }
    return ret;
  }

 public:
  int beautifulNumbers(int l, int r) {
    ll ans = Cal(r) - Cal(l - 1);
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

int main() {  //
  Solution s;
  // cout << s.beautifulNumbers(1, 100) << endl;
  // cout << s.beautifulNumbers(1, 200) << endl;
  // cout << s.beautifulNumbers(1, 1000) << endl;
  // cout << s.beautifulNumbers(1, 10000) << endl;
  // cout << s.beautifulNumbers(1, 100000) << endl;
  // cout << s.beautifulNumbers(1, 1000000) << endl;
  // cout << s.beautifulNumbers(1, 10000000) << endl;
  // cout << s.beautifulNumbers(1, 100000000) << endl;
  // cout << s.beautifulNumbers(1, 1000000000) << endl;
  return 0;
}

#endif
