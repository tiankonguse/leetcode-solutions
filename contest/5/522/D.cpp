
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

typedef long long ll;
const ll mod = 1e9 + 7;

struct Matrix {
  ll P;
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 1) : sz(sz) {  //
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
  Matrix operator*(const Matrix& B) const {
    Matrix ret(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        for (int k = 0; k < sz; k++) ret.a[i][j] = (ret.a[i][j] + a[i][k] * B.a[k][j]) % P;
    return ret;
  }
  Matrix pow(ll k) const {
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
  int countGoodStrings(ll n) {
    // f(n) = f(n-1) + f(n-2)
    //
    //
    // f(0) = 0
    // f(1) = 2, a | b
    // f(2) = 2, ab | ba
    // f(3) = 4,  aba, bab, aaa, bbb
    // f(4) = 6,  aaab, abbb, bbba, baaa, abab, baba, aaab,bbba
    Matrix unit(2);
    unit.a[0][0] = 0;
    unit.a[0][1] = 1;
    unit.a[1][0] = 1;
    unit.a[1][1] = 1;
    Matrix ans = unit.pow(n);
    MyPrintf("[0,0] = %lld\n", ans.a[0][0]);
    MyPrintf("[0,1] = %lld\n", ans.a[0][1]);
    MyPrintf("[1,0] = %lld\n", ans.a[1][0]);
    MyPrintf("[1,1] = %lld\n", ans.a[1][1]);
    return (ans.a[0][1] * 2) % mod;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif