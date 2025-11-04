class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};