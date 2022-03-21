#include "base.h"

// GCD 相关算法

// 推论1：有俩个数p,q,且gcd(q,p)=1,则最大无法表示成px+qy（x>=0,y>=0)的数是pq-q-p.

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}

// 浮点数 GCD
#define eps 1e-8
// fmod 系统函数
double Fgcd(double a, double b) {
  if (b > -eps && b < eps) {
    return a;
  } else {
    return Fgcd(b, fmod(a, b));
  }
}

// 扩展 GCD
int Exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int d = Exgcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - a / b * y;
  return d;
}

// 逆元
ll ModInverse(ll b, ll c){
    ll x, y;
    Exgcd(b, c, x, y);
    return (x%c + c) % c;
}

// 求(a/b)% c(乘法逆元)
int DivMod(int a, int b, int c) {
  int x = ModInverse(b, c);
  return ((a % c) * (x % c)) % c;
}

// 乘法取模
ll MulMod(ll a, ll b, ll c) {
  ll res = 0LL;
  for (; b; b >>= 1, a = (a << 1) % c) {
    if (b & 1) res = (res + a) % c;
  }
  return res;
}

// 快速幂
ll PowMod(ll a, ll b, ll c) {
  ll res = 1LL;
  for (; b; b >>= 1, a = MulMod(a, a, c)) {
    if (b & 1) res = MulMod(res, a, c);
  }
  return res;
}



int main() { return 0; }
