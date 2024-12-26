// #include "base.h"

#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
typedef vector<string> vs;

// const int mod = 1e9 + 7;

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep1(i, n) for (ll i = 1; i <= (n); i++)
#define rrep(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep1(i, n) for (ll i = (n); i >= 1; i--)
#define all(v) (v).begin(), (v).end()

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
void chmin(T& a, T b) {
  a = min(a, b);
}
template <class T>
void chmax(T& a, T b) {
  a = max(a, b);
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

/*
unordered_map / unordered_set

lower_bound 大于等于
upper_bound 大于
reserve 预先分配内存
reverse(all(vec)) 反转
sum = accumulate(a.begin(), a.end(), 0ll);
__builtin_popcount 一的个数
vector / array : upper_bound(all(vec), v)
map: m.upper_bound(v)

区间个数： std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)



size_t found=str.find(string/char/char*);
std::string::npos

排序，小于是升序：[](auto&a, auto&b){ return a < b; })
优先队列 priority_queue<Node>：top/pop/push/empty
struct Node {
  Node(int t = 0) : t(t) {}
  int t;
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& that) const { return this->t < that.t; }
};
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 20010;
const int kMaxVal = 10e8;

int maxNM;

vll A;

struct SegTree {
  pll sign[maxn << 2];  //
  ll Dis[maxn << 2];

  void PushDown(int rt) {
    if (sign[rt].first) {
      ll al = sign[rt].second;
      ll ar = al + Dis[rt << 1];
      sign[rt << 1] = {1, al};
      sign[rt << 1 | 1] = {1, ar};
      sign[rt] = {0, 0};
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = {0, 0};
    Dis[rt] = r - l + 1;
    if (l == r) {
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
  }
  void update(int L, int R, int offset, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = {1, offset + (l - L)};
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, offset, lson);
    if (R > m) update(L, R, offset, rson);
  }
  ll query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      ll al = sign[rt].second;
      return A[al];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = -1;
    if (L <= m) {
      ret = query(L, R, lson);
    }
    if (m < R) {
      ret = query(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;

int main() {
  ll n, m;
  scanf("%lld", &n);
  A.resize(n + 1, -1);
  rep1(i, n) { scanf("%lld", &A[i]); }

  maxNM = n;

  segTree.Build();

  scanf("%lld", &m);
  rep(i, m) {
    ll o, k, x, y;
    scanf("%lld", &o);
    if (o == 1) {
      scanf("%lld%lld%lld", &k, &x, &y);
      if (x + k - 1 > n) {
        k = n - x + 1;
      }
      if (y + k - 1 > n) {
        k = n - y + 1;
      }
      ll bl = y, br = y + k - 1;
      // printf("update i=%lld x=%lld k=%lld bl=%lld br=%lld\n", i, x, k, bl, br);
      segTree.update(bl, br, x);
    } else {
      scanf("%lld", &x);
      // printf("query i=%lld x=%lld v=?\n", i, x);
      printf("%lld\n", segTree.query(x, x));
    }
  }

  return 0;
}
