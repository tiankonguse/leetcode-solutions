// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}

ll Mul(ll a, ll b) { return a * b % mod1e7; }
ll Add(ll a, ll b) { return (a + b) % mod1e7; }

struct Matrix {
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 1) : sz(sz) {  //
    init(sz);
  }
  void init(int n) {
    sz = n;
    a.clear();
    a.resize(n, vector<ll>(n, 0));
  }
  void _union() {
    int l = sz;
    while (l--) {
      a[l][l] = 1;
    }
  }
  Matrix operator*(const Matrix& B) {
    Matrix ret(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        for (int k = 0; k < sz; k++)
          ret.a[i][j] = (ret.a[i][j] + a[i][k] * B.a[k][j]) % mod1e7;
    return ret;
  }
  Matrix pow(ll k) {
    Matrix ret(sz);
    Matrix A = *this;
    ret._union();
    while (k) {
      if (k & 1) ret = ret * A;
      A = A * A;
      k >>= 1;
    }
    return ret;
  }
};

class Solution {
  int n;
  ll T, S;

  int SolverEx(const string& s, const string& t, ll k) {
    if (s[0] == s[1]) {  // "aa"
      if (s == t) {
        return 1;
      } else {
        return 0;
      }
    } else {  // "ab"
      if (s[0] == t[0] && s[1] == t[1]) {
        if (k % 2 == 0) {
          return 1;
        } else {
          return 0;
        }
      } else if (s[0] == t[1] && s[1] == t[0]) {
        if (k % 2 == 1) {
          return 1;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    }
  }

 public:
  int numberOfWays(const string& s, const string& t, ll k) {
    n = s.size();
    // 长度为 2 特殊处理

    if (n == 2) {
      return SolverEx(s, t, k);
    }

    Init(s.c_str(), n);

    S = h[n - 1];  // s 的 hash 值
    // 计算目标的 hash 值
    T = 0;
    for (int i = 0; i < n; i++) {
      T = (T * BASE + (t[i] - 'a' + 1)) % mod1e7;
    }
    int num0 = 0;
    if (T == S) {
      num0 = 1;
    }

    int num1 = 0;  // 移动 1 ~ n-1 次，有几次与目标一致
    for (int i = 1; i < n; i++) {
      ll LN = i;
      ll LH = H(0, i - 1);
      ll RH = H(i, n - 1);

      ll tmp = Add(Mul(RH, qpowCache[LN]), LH);
      if (tmp == T) {
        num1++;
      }
    }
    printf("num0=%d num1=%d\n", num0, num1);

    Matrix A(2);
    A.a[1][0] = 1;

    Matrix B(2);
    B.a[0] = {0, 1};
    B.a[1] = {n - 1, n - 2};

    Matrix C = A * (B.pow(k));

    return Add(Mul(num0, C.a[0][0]), Mul(num1, C.a[0][1]));
  }
};
