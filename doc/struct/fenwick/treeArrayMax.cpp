
// 树状数组求前缀最大值
class TreeArrayMax {
 public:
  void Init(int n_) {  // [1,n]
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll QueryMax(int x) {  // [1,n]
    ll s = 0;
    while (x > 0) {
      s = max(s, c[x]);
      x -= Lowbit(x);
    }
    return s;
  }

  void SetVal(int x, ll v) {  // [1,n]
    while (x <= n) {
      c[x] = max(c[x], v);
      x += Lowbit(x);
    }
  }

 private:
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};