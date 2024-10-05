
mt19937 rnd(time(0));

struct Matrix {
  ll P;
  int sz;
  vector<vector<ll>> a;
  Matrix(int sz = 1) : sz(sz) {  //
    init(sz);
  }
  void init(int n, ll p = 998244353) {
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
  Matrix operator*(Matrix& B) {
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