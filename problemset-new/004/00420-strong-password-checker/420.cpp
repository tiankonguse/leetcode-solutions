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

int dp[55][55][66][66][8];

class Solution {
  string s;

  map<char, int> baseIndex;
  void init() {
    int index = 0;
    baseIndex[' '] = index++;
    for (char c = 'a'; c <= 'z'; c++) {
      baseIndex[c] = index++;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
      baseIndex[c] = index++;
    }
    for (char c = '0'; c <= '9'; c++) {
      baseIndex[c] = index++;
    }
    baseIndex['.'] = index++;
    baseIndex['!'] = index++;
  }

  int I(char c) { return baseIndex[c]; }

  int H(char c) {
    if ('a' <= c && c <= 'z') return 1 << 0;
    if ('A' <= c && c <= 'Z') return 1 << 1;
    if ('0' <= c && c <= '9') return 1 << 2;
    return 0;
  }
  pii MaxContinueLen() {
    int ans = 1;
    char pre = ' ';
    int preLen = 0;
    set<int> group;
    group.insert(0);
    for (auto c : s) {
      group.insert(H(c));
      if (c == pre) {
        preLen++;
        chmax(ans, preLen);
      } else {
        pre = c;
        preLen = 1;
      }
    }

    return {ans, int(group.size() - 1)};
  }

  int SolverEx(int n) {  //
    auto [maxLen, maskNum] = MaxContinueLen();
    if (n <= 2) return 6 - n;
    if (n == 3) {
      return 3; // 插入在中间
    } else if (n == 4) {
      if (maskNum > 0) {
        return 2;  // 补两个
      } else {
        return 3;  // 修改一个，补两个
      }
    } else if (n == 5) {
      if (maxLen >= 3) {
        if (maskNum == 0) {
          return 3;  // 修改两个，补一个
        } else if (maskNum == 1) {
          return 2;  // 修改一个，补一个
        } else {     // maskNum >= 2
          return 1;  // 插入在中间
        }
      } else if (maskNum == 3) {
        return 1;
      } else {
        return 3 - maskNum;  // 缺几个，操作几次
      }
    }
    return Solver(n);
  }

  int dfs(int n, int m, int p1, int p2, int flag) {
    int& ret = dp[n][m][p1][p2][flag];
    if (ret != -1) return ret;

    if (n + m < 6) return ret = 100;  //无解
    if (n == 0) {
      if (m > 20 || flag != 7) return ret = 100;  // 无解
      return ret = 0;
    }

    char c = s[n - 1];
    int p0 = I(c);
    int mask = H(c);

    ret = 100;
    chmin(ret, 1 + dfs(n - 1, m, p1, p2, flag));  // 删除

    if (p0 != p1 || p0 != p2 || p1 != p2) {
      chmin(ret, dfs(n - 1, m + 1, p0, p1, flag | mask));  // 可以保留
    }

    // 修改
    rep(i, 3) {
      chmin(ret, 1 + dfs(n - 1, m + 1, I(' '), I('.'),
                         flag | (1 << i)));  // 修改为 1<<i
    }

    return ret;
  }

  int Solver(int n) {  //
    memset(dp, -1, sizeof(dp));
    return dfs(n, 0, 0, 0, 0);
  }

 public:
  int strongPasswordChecker(string& s_) {
    s.swap(s_);
    init();
    return SolverEx(s.length());
  }
};

int main() {
  int ans;
  string s;

  ans = 5;
  s = "a";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  ans = 3;
  s = "aA1";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  ans = 0;
  s = "1337C0d3";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  ans = 1;
  s = "aaaB1";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  ans = 1;
  s = "aA123";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  ans = 3;
  s = "...";
  TEST_SMP1(Solution, strongPasswordChecker, ans, s);

  return 0;
}
