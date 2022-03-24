#include "base.h"

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
#define rrep1(i, n) for (ll i = (n); i >= 0; i--)
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
  ll Get(ll pre, ll n) {
    ll ans = 0;
    ll l = pre, r = pre;
    while (l <= n) {
      ans += min(r, n) - l + 1;
      l = l * 10;
      r = r * 10 + 9;
    }
    return ans;
  }

 public:
  int findKthNumber(ll n, ll k) {
    ll ans = 1;
    k--;
    while (k > 0) {
      ll sum = Get(ans, n);
      if (sum <= k) {
        k -= sum;
        ans++;
      } else {
        k--;
        ans *= 10;
      }
    }
    return ans;
  }
};

int main() {
  int ans = 1;
  int n = 10, k = 1;

  n = 10, k = 2, ans = 10;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 10, k = 3, ans = 2;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 1, ans = 1;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 2, ans = 10;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 3, ans = 100;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 4, ans = 101;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 5, ans = 11;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 6, ans = 12;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 7, ans = 13;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 8, ans = 14;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 9, ans = 15;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 10, ans = 16;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 11, ans = 17;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 12, ans = 18;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 13, ans = 19;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 101, k = 14, ans = 2;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  n = 10000, k = 10000, ans = 9999;
  TEST_SMP2(Solution, findKthNumber, ans, n, k);

  return 0;
}
