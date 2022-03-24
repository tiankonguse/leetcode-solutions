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
  string s, p;
  ll n, m;
  vvll dp;

  ll Dfs(ll l, ll r) {
    if (l == 0 && r == 0) return 1;
    if (l == 0 && r == 1 && p[0] == '*') return 1;
    if (l == 0 || r == 0) return 0;

    ll& ret = dp[l][r];
    if (ret != -1) {
      return ret;
    }
    if (s[l - 1] == p[r - 1] || p[r - 1] == '?') {
      return ret = Dfs(l - 1, r - 1);
    }
    if (p[r - 1] != '*') {
      return ret = 0;
    }
    for (ll i = 0; i <= l; i++) {
      if (Dfs(l - i, r - 1)) {
        return ret = 1;
      }
    }

    return ret = 0;
  }
  void Init() {
    string tmp;
    for (auto c : p) {
      if (tmp.length() == 0) {
        tmp.push_back(c);
      } else {
        if (tmp.back() == '*' && c == '*') {
          continue;
        } else {
          tmp.push_back(c);
        }
      }
    }
    p.swap(tmp);
  }

 public:
  bool isMatch(string& s_, string& p_) {
    s.swap(s_);
    p.swap(p_);
    Init();
    n = s.length();
    m = p.length();
    dp.resize(n + 1, vll(m + 1, -1));
    return Dfs(n, m);
  }
};

int main() {
  bool ans;
  string s, p;

  ans = false;
  s = "aa";
  p = "a";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  ans = true;
  s = "aa";
  p = "*";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  ans = false;
  s = "cb";
  p = "?a";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  ans = true;
  s = "adceb";
  p = "*a*b";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  ans = false;
  s = "acdcb";
  p = "a*c?b";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  ans = false;
  s = "mississippi";
  p = "m??*ss*?i*pi";
  TEST_SMP2(Solution, isMatch, ans, s, p);

  return 0;
}
