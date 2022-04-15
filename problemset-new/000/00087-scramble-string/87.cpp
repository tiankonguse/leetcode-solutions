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

int dp[33][33][33][33];

class Solution {
  int n;
  string s1;
  string s2;

  bool Dfs(int s1l, int s1r, int s2l, int s2r) {
    int& ret = dp[s1l][s1r][s2l][s2r];
    if (ret != -1) return ret;

    if (s1l == s1r) {
      if (s1[s1l] == s2[s2l]) {
        ret = 1;
      } else {
        ret = 0;
      }
      return ret;
    }

    int len = s1r - s1l + 1;
    for (int mid = 1; mid < len; mid++) {  // [l, mid][mid+1, r]
      int leftLen = mid;
      int rightLen = len - leftLen;

      // 原封不动
      if (Dfs(s1l, s1l + mid - 1, s2l, s2l + mid - 1) &&
          Dfs(s1l + mid, s1r, s2l + mid, s2r)) {
        return ret = 1;
      }

      // 左右交换
      if (Dfs(s1l + mid, s1r, s2l, s2l + rightLen - 1) &&
          Dfs(s1l, s1l + mid - 1, s2l + rightLen, s2r)) {
        return ret = 1;
      }
    }
    return ret = 0;
  }

 public:
  bool isScramble(string& s1_, string& s2_) {
    s1.swap(s1_);
    s2.swap(s2_);
    n = s1.length();
    memset(dp, -1, sizeof(dp));

    return Dfs(0, n - 1, 0, n - 1);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
