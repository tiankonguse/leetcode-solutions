/*
ST 表（Sparse Table，稀疏表）是用于解决 可重复贡献问题 的数据结构。

opt 必须满足结合律才能使用 ST 表求解。
另外，根据 opt 是数值类问题还是集合类问题，ST 表查询的复杂度也不一样。


集合类幂等问题，一般是可重复贡献问题。
可重复贡献问题 是指对于运算 opt，满足 𝑥 opt⁡ 𝑥 =
𝑥，则对应的区间询问就是一个可重复贡献问题。
例如，最大值有 max(𝑥,𝑥) =𝑥，gcd 有 gcd⁡(𝑥,𝑥) =𝑥，所以 RMQ 和区间 GCD
就是一个可重复贡献问题。 一般有 最大值、最小值、最大公约数、最小公倍数、按位或、按位与等。
查询方式：拆分为两个有重叠的区间
查询复杂度：O(1)
ll MaxOpt(ll a, ll b) { return max(a, b); }
ll MinOpt(ll a, ll b) { return min(a, b); }
ll GcdOpt(ll a, ll b) { return __gcd(a, b); }
ll LcmOpt(ll a, ll b) { return a / __gcd(a, b) * b; }
ll OrOpt(ll a, ll b) { return a | b; }
ll AndOpt(ll a, ll b) { return a & b; }


数值类问题，一般是不可重复贡献问题。
不可重复贡献问题 是指对于运算 opt，不满足 𝑥 opt⁡ 𝑥 =
𝑥，则对应的区间询问就是一个不可重复贡献问题。 例如，求和有 sum(𝑥,𝑥) =2𝑥，所以区间和就是一个不可重复贡献问题。 一般有
求和、求积、异或等。
查询方式：二进制拆分 + ST 表
查询复杂度：O(logn)
ll SumOpt(ll a, ll b) { return a + b; }
ll XorOpt(ll a, ll b) { return a ^ b; }
ll MulOpt(ll a, ll b) { return a * b; }
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max3 = 2010, max4 = 50010, max5 = 500010, max6 = 2000010;

int base2[max4];
void InitBase2(int n) {
  base2[1] = 0;
  for (int i = 2; i <= n; i++) {
    base2[i] = base2[i >> 1] + 1;
  }
}
// 使用内建函数计算 ⌊ log_2 x ⌋
inline int lg2(ll x) { return 31 - __builtin_clz(x); }  // 内建函数，O(1)
inline int Log2(ll x) { return base2[x]; }
// inline int Lg(int x) { return __lg(x); } // 内建函数，O(1)
inline int Log(ll x) { return Log2(x); }
const int kMaxLog = 16;

ll stMax[kMaxLog][max4];
inline ll Max(const ll a, const ll b) { return a > b ? a : b; }
inline ll QueryMax(const int a, const int b) {
  const int k = lg2(b - a + 1);
  ll left = stMax[k][a];
  ll right = stMax[k][b - (1 << k) + 1];
  return Max(left, right);
}

ll stMin[kMaxLog][max4];
inline ll Min(const ll a, const ll b) { return a < b ? a : b; }
inline ll QueryMin(const int a, const int b) {
  const int k = lg2(b - a + 1);
  ll left = stMin[k][a];
  ll right = stMin[k][b - (1 << k) + 1];
  return Min(left, right);
}

ll stSum[kMaxLog][max4];
inline ll Sum(const ll a, const ll b) { return a + b; }
inline ll QuerySum(const int a, const int b) {
  int K = b - a + 1;
  if (K & (K - 1) == 0) {
    const int k = lg2(K);
    return stSum[k][a];
  } else {
    ll o = a;
    ll ret = stSum[0][o];
    K--, o++;
    for (int k = 0; K; k++) {
      if (K & 1) {
        ret = Sum(ret, stSum[k][o]);
        o += 1 << k;
      }
      K >>= 1;
    }
    return ret;
  }
}

void InitSparseTable(int n, ll nums[]) {
  int maxLog = Log(n) + 1;
  stSum[0][0] = stMax[0][0] = stMin[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    stSum[0][i] = stMax[0][i] = stMin[0][i] = nums[i];
  }
  for (int k = 1; k < maxLog; k++) {
    for (int i = 0; i + (1 << k) - 1 <= n; i++) {
      stSum[k][i] = Sum(stSum[k - 1][i], stSum[k - 1][i + (1 << (k - 1))]);
      stMax[k][i] = Max(stMax[k - 1][i], stMax[k - 1][i + (1 << (k - 1))]);
      stMin[k][i] = Min(stMin[k - 1][i], stMin[k - 1][i + (1 << (k - 1))]);
    }
  }
}
