/*
带版本的取模树状数组

TreeArray treeArray;
treeArray.Init(n);
treeArray.NextTick(); // 清空树状数组
treeArray.Add(x, v); // 单点更新
treeArray.Query(x, y); // 区间查询 [x,y]

*/

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
int tick = 0;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    // c.clear();
    c.resize(n + 100, 0);
    // times.clear();
    times.resize(n + 100, 0);
  }
  void NextTick() { tick++; }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      if (times[x] == tick) {
        s = (s + c[x]) % mod;
      }
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) {
    if (l > r) return 0;
    return (Query(r) - Query(l - 1) + mod) % mod;
  }

  void Add(int x, ll v) {
    while (x <= n) {
      if (times[x] != tick) {
        times[x] = tick;
        c[x] = 0;
      }
      c[x] = (c[x] + v) % mod;
      x += Lowbit(x);
    }
  }

 private:
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  vector<ll> times;
  int n;
};