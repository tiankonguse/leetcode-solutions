// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

struct Matrix {
  ll P;
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 26) : sz(sz) {  //
    init(sz);
  }
  void init(int n, ll p = mod) {
    P = p;
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
          ret.a[i][j] = (ret.a[i][j] + a[i][k] * B.a[k][j]) % P;
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
 public:
  int lengthAfterTransformations(const string& s, int t, vector<int>& nums) {
    Matrix base(26);
    for (auto c : s) {
      base.a[0][c - 'a']++;
    }

    Matrix mat(26);
    for (int i = 0; i < 26; i++) {
      int v = nums[i];
      int j = i;
      while (v--) {
        j = (j + 1) % 26;
        mat.a[i][j]++;
      }
    }
    Matrix tmp = base * mat.pow(t);
    ll ans = 0;
    for (int i = 0; i < 26; i++) {
      ans = (ans + tmp.a[0][i]) % mod;
    }
    return ans;
  }
};