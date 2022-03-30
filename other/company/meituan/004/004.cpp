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

class Solution {
 public:
  int minJump(vector<int>& jump) {
    int n = jump.size();

    return 0;
  }
};

ll n, m;
struct Op {
  ll o, k, x, y;
  void Read() {
    scanf("%lld", &o);
    if (o == 1) {
      scanf("%lld%lld%lld", &k, &x, &y);
      Fix();
    } else {
      scanf("%lld", &x);
      y = -1;
    }
  }
  void Fix() {
    if (x + k > n) {
      k = n - x + 1;
    }
    if (y + k > n) {
      k = n - y + 1;
    }
  }
};

int main() {
  scanf("%lld", &n);

  vll A(n + 1), B(n + 1, -1);
  rep1(i, n) { scanf("%lld", &A[i]); }

  scanf("%lld", &m);
  vector<Op> ops(m);
  rep(i, m) { ops[i].Read(); }

  map<ll, set<ll>> q;
  rrep(i, m) {
    if (ops[i].o == 2) {
      q[ops[i].x].insert(i);
      //   printf("query i=%lld x=%lld v=?\n", i, ops[i].x);
    } else {
      ll x = ops[i].x, y = ops[i].y, k = ops[i].k;
      //   printf("modify i=%lld x=%lld y=%lld k=%lld\n", i, x, y, k);
      ll bl = y, br = y + k - 1;

      auto it = q.lower_bound(bl);
      while (it != q.end() && it->first <= br) {
        int dis = it->first - bl + 1;
        int realPos = x + dis - 1;
        for (auto j : it->second) {
          ops[j].y = A[realPos];
        }
        q.erase(it++);
      }
    }
  }

  rep(i, m) {
    if (ops[i].o == 2) {
      printf("%lld\n", ops[i].y);
    }
  }

  return 0;
}
