#include <bits/stdc++.h>

#include "base.h"
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
#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define sz(x) (int)(x).size()
#define SZ(A) int((A).size())
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define CTN(T, x) (T.find(x) != T.end())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
inline void RST(T& A) {
  memset(A, 0, sizeof(A));
}
template <class T>
inline void FLC(T& A, int x) {
  memset(A, x, sizeof(A));
}
template <class T>
inline void CLR(T& A) {
  A.clear();
}
template <class T>
T& chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
  return a;
}
template <class T>
T& chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
  return a;
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// LONG_MIN(10进制 10位), LONG_MAX(10进制 19位)

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

vector 去重
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

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

srand((unsigned)time(NULL));
rand();

mt19937 gen{random_device{}()};
uniform_real_distribution<double> dis(min, max);
function<double(void)> Rand = [that = this]() { return that->dis(that->gen); };

*/

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  ll ans = 0;
  ll maxValue;
  ll kMaxLen = 15;
  ll n;
  // dp[i][j] 以 i 开头的长度为 j 的值互不相同的子序列个数
  vector<vector<ll>> dp;

  // dp[i][j] 长度为 n，个数 为 j 的不同序列个数
  vector<vector<ll>> dp2;

  int Dfs(int start) {
    if (dp[start][0] != -1) return dp[start][0];

    for (int i = 0; i < kMaxLen; i++) {
      dp[start][i] = 0;
    }

    dp[start][1] = 1;  // 自身
    int maxLen = 1;

    for (ll base = 2; base * start <= maxValue; base++) {
      ll next = start * base;
      int nextLen = Dfs(next);
      for (int i = 1; i <= nextLen; i++) {
        dp[start][i + 1] += dp[next][i];
      }
      maxLen = max(maxLen, 1 + nextLen);
    }
    return dp[start][0] = maxLen;
  }

  ll Dfs2(int n, int k) {  // 至少一个
    if (n <= 0 || k <= 0) return 0;
    if (n < k) return 0;
    if (k == 1) return 1;
    if (n == k) return 1;
    return Dfs3(n - k, k);
  }

  ll Dfs3(int n, int k) {  // 可以为空
    if (n <= 0 || k <= 0) return 0;
    if (k == 1) return 1;

    ll& ret = dp2[n][k];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 1; i <= k; i++) {
      ret = (ret + Dfs2(n, i) * C(k, i)) % mod;
    }

    return ret;
  }

  const int N = 20;
  vector<vector<ll>> str;
  int C(int m, int n) {
    if (str[m][n] != -1) return str[m][n];
    if (m == n || n == 0) return str[m][n] = 1;
    if (m < n) return str[m][n] = 0;
    return str[m][n] = C(m - 1, n - 1) + C(m - 1, n);
  }

 public:
  int idealArrays(int n_, int maxValue_) {
    maxValue = maxValue_;
    n = n_;
    str.resize(N, vector<ll>(N, -1));

    dp.resize(maxValue + 1, vector<ll>(kMaxLen, -1));

    for (int i = 1; i <= maxValue; i++) {
      Dfs(i);
    }

    dp2.resize(n + 1, vector<ll>(kMaxLen, -1));
    for (int i = 1; i <= maxValue; i++) {
      for (int j = 1; j <= dp[i][0] && j <= n; j++) {
        // printf("i=%d j=%d count=%lld ans=%lld\n", i, j, dp[i][j], Dfs2(n,
        // j));
        ans = (ans + dp[i][j] * Dfs2(n, j)) % mod;
      }
      // printf("i=%d ans=%lld\n", i, ans);
    }

    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
