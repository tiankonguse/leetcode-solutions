/*
ID: tiankonguse
TASK: game
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7814
*/
#define TASK "game"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const ll BASE = 29;

const int N = 2000010;
const int M = 26;
char str[N];
void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

mt19937 rnd(time(0));

struct Matrix {
  ll P;
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 2) : sz(sz) {  //
    Init(sz);
  }
  void Init(int n, ll p = 998244353) {
    P = p;
    sz = n;
    a.clear();
    a.resize(n, vector<ll>(n, 0));
  }
  void Union() {
    int l = sz;
    while (l--) {
      a[l][l] = 1;
    }
  }
  bool IsUnion() {
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < sz; j++) {
        if (i == j && a[i][j] != 1) return false;
        if (i != j && a[i][j] != 0) return false;
      }
    }
    return true;
  }
  Matrix operator*(Matrix& B) {
    Matrix ret(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        for (int k = 0; k < sz; k++)
          ret.a[i][j] = (ret.a[i][j] + a[i][k] * B.a[k][j]) % P;
    return ret;
  }
  Matrix Inv() { return Pow(P - 2); }
  bool IsInv() { return Pow(P - 1).IsUnion(); }
  Matrix Pow(ll k) {
    Matrix ret(sz);
    Matrix A = *this;
    ret.Union();
    while (k) {
      if (k & 1) ret = ret * A;
      A = A * A;
      k >>= 1;
    }
    return ret;
  }
  void Rand() {
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++) {
        a[i][j] = rnd() % P;
      }
  }
  ull Hash() {
    ull res = 0;
    for (int i = 0; i < sz; i++) {
      ull tmp = 1;
      for (int j = 0; j < sz; j++) {
        tmp *= a[i][j];
      }
      res ^= tmp;
    }
    return res;
  }
};

/*

*/

void Solver() {
  ll n;
  scanf("%lld%s", &n, str);
  vector<Matrix> mat(M), rmat(M);
  for (int i = 0; i < 26; i++) {
    Matrix& t = mat[i];
    t.Rand();
    while (!t.IsInv()) t.Rand();
    rmat[i] = t.Inv();
  }

  ll ans = 0;
  Matrix pre(2);
  pre.Union();
  unordered_map<ll, ll> h;
  h[pre.Hash()]++;
  for (int i = 0; i < n; i++) {
    const char c = str[i];
    const ll v = c - 'a';
    pre = pre * (i & 1 ? mat[v] : rmat[v]);
    ull tmp = pre.Hash();
    ans += h[tmp];
    h[tmp]++;
  }

  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
accabccb

*/