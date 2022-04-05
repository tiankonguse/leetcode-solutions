#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef __int128_t ll;
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

typedef ld BigNum;

BigNum dp[9][25][9][25][9];
BigNum dpAll[9][50];
BigNum dpC[50][50];

class Solution {
  vector<int> balls;

  BigNum C(ll m, ll n) {
    if (m < 0 || n < 0) return 0;
    if (dpC[m][n] >= 0) return dpC[m][n];
    if (m == n || n == 0) return dpC[m][n] = 1;
    if (m < n) return dpC[m][n] = 0;
    return dpC[m][n] = C(m - 1, n - 1) + C(m - 1, n);
  }

  BigNum DfsAll(int k, int n) {
    if (n < 0) return 0;
    if (k == -1) return n == 0;

    auto& ret = dpAll[k][n];
    if (ret >= 0) {
      // printf("k=%d n=%d ret=%Lf\n", k, n, ret);
      return ret;
    }
    ret = C(n, balls[k]) * DfsAll(k - 1, n - balls[k]);
    // printf("k=%d n=%d ret=%Lf\n", k, n, ret);
    return ret;
  }

  BigNum Dfs(int k, int n, int l, int m, int r) {
    if (n < 0 || l < 0 || m < 0 || r < 0) return 0;
    if (k == -1) return int(n == 0 && l == 0 && m == 0 && r == 0);
    auto& ret = dp[k][n][l][m][r];
    if (ret >= 0) {
      return ret;
    }

    int num = balls[k];
    ret = 0;
    for (int i = 0; i <= num; i++) {
      int j = num - i;
      auto base = C(n, i) * C(m, j);
      ret += base * Dfs(k - 1, n - i, l - (i > 0), m - j, r - (j > 0));
    }
    return ret;
  }

 public:
  double getProbability(vector<int>& balls_) {
    balls.swap(balls_);
    int sum = 0;
    for (auto v : balls) {
      sum += v;
    }

    int k = balls.size();
    int n = sum / 2;

    memset(dp, -1, sizeof(dp));
    memset(dpAll, -1, sizeof(dpAll));
    memset(dpC, -1, sizeof(dpC));
    BigNum ans = 0;
    for (int i = (k + 1) / 2; i <= k; i++) {
      ans += Dfs(k - 1, n, i, n, i);
    }

    BigNum all = DfsAll(k - 1, sum);
    // printf("ans=%Lf all=%Lf\n", ans, all);

    return ans * 1.0 / all;
  }
};

int main() {
  double ans;
  vi balls;

  ans = 1.0;
  balls = {1, 1};
  TEST_SMP1(Solution, getProbability, ans, balls);

  ans = 0.66667;
  balls = {2, 1, 1};
  TEST_SMP1(Solution, getProbability, ans, balls);

  ans = 0.60000;
  balls = {1, 2, 1, 2};
  TEST_SMP1(Solution, getProbability, ans, balls);

  return 0;
}
