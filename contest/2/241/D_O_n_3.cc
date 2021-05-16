#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;
const int max3 = 1100;
const int mod = 1000000007;

ll dp[max3][max3];
ll strA[max3];
ll strC[max3][max3];

class Solution {
  void Init(int n) {
    memset(dp, -1, sizeof(dp));
    memset(strC, -1, sizeof(strC));

    strA[0] = 1;
    for (int i = 1; i <= n; i++) {
      strA[i] = (strA[i - 1] * i) % mod;
    }
  }

  int funC(int m, int n) {
    if (strC[m][n] != -1) return strC[m][n];
    if (m == n || n == 0) return strC[m][n] = 1;
    if (m < n) return strC[m][n] = 0;
    return strC[m][n] = (funC(m - 1, n - 1) + funC(m - 1, n)) % mod;
  }

  ll funA(int n, int m) { return strA[n]; }

  // 下标从 1 开始， [1, n][1, k]
  ll dfs(const int n, const int k) {
    if (dp[n][k] != -1) return dp[n][k];
    if (k > n) return dp[n][k] = 0;
    if (k == n) return dp[n][k] = 1;
    if (k == 1) return dp[n][k] = funA(n - 1, n - 1);

    // printf("n=%d k=%d\n", n, k);

    // n > k >= 2
    // i = k >= 2
    ll ans = 0;
    for (int i = k; i <= n; i++) {
      int left = i - 1, right = n - i;

      ll c = funC(n - 1, right);
      ll a = funA(right, right);
      ll b = dfs(left, k - 1);
      ll tmp = (b * (a * c % mod)) % mod;
      ans = (ans + tmp) % mod;
      // printf("i=%d b=%lld a=%lld c=%lld tmp=%lld ans=%lld\n", i, b, a, c,
      // tmp, ans);
    }
    return dp[n][k] = ans % mod;
  }

 public:
  int rearrangeSticks(int n, int k) {
    Init(n);
    return dfs(n, k);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
