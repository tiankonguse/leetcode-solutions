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

class Solution {
 public:
  int minJump(vector<int>& jump) {
    int n = jump.size();

    return 0;
  }
};

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

vvll m;
vvll sums;
ll r = 100;
ll d;

void Init(ll n) {
  d = 2 * r + 1;
  m.resize(d + 1, vll(d + 1, 0));
  m[r][r] = n;

  bool flag = true;
  while (flag) {
    flag = false;
    rep(i, d) {
      rep(j, d) {
        ll v = m[i][j];
        if (v < 8) continue;
        // printf("i=%lld j=%lld v=%lld\n", i, j, v);
        flag = true;
        rep(k, 8) {
          ll x = i + dir8[k][0], y = j + dir8[k][1];
          m[x][y] += v / 8;
        }
        m[i][j] %= 8;
        // printf("i=%lld j=%lld v=%lld\n", i, j, m[i][j]);
      }
    }
  }

  sums.resize(d + 1, vll(d + 1, 0));
  rep1(i, d) {
    rep1(j, d) {
      //   if (m[i][j] > 0) printf("i=%lld j=%lld v=%lld\n", i, j, m[i][j]);
      sums[i][j] =
          m[i][j] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
    }
  }
}

int main() {
  ll n, q;
  scanf("%lld%lld", &n, &q);
  Init(n);

  while (q--) {
    ll x1, y1, x2, y2;
    scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
    x1 += r, y1 += r, x2 += r, y2 += r;
    if (x1 > x2) {
      swap(x1, x2);
    }
    if (y1 > y2) {
      swap(y1, y2);
    }
    chmax(x1, 1ll);
    chmax(y1, 1ll);
    chmin(x2, d);
    chmin(y2, d);

    printf("%lld\n", sums[x2][y2] - sums[x2][y1 - 1] - sums[x1 - 1][y2] +
                         sums[x1 - 1][y1 - 1]);
  }

  return 0;
}
