
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;

mt19937 rnd(time(0));

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
enum { UP = 0, DOWN = 1 };
class Solution {
 public:
  int zigZagArrays(int n, int l, int r) {
    int R = r - l + 1;
    int R2 = R * 2;
    Matrix state(R2);
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < R; j++) {  // DOWN -> UP
        if (j > i) {
          state.a[i][R + j] = 1;
        }
      }
      for (int j = 0; j < R; j++) {
        if (j < i) {
          state.a[R + i][j] = 1;
        }
      }
    }
    Matrix stateN = state.pow(n - 1);
    ll ans = 0;
    for (int i = 0; i < R2; i++) {
      for (int j = 0; j < R2; j++) {
        ans = (ans + stateN.a[i][j]) % mod;
      }
    }

    return ans;
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