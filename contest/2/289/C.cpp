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

typedef pair<int, int> pii;
typedef vector<pii> vpii;

// left 0, up 1, right 2, down 3
class Solution {
  vector<vector<vector<pii>>> dp;  // <2, 5>
  vector<vector<int>> grid;
  int n, m;

  void Add(pii& p, int v) {
    while (v > 0 && v % 2 == 0) {
      p.first++;
      v /= 2;
    }

    while (v > 0 && v % 5 == 0) {
      p.second++;
      v /= 5;
    }
  }

  void InitLeft(int dir) {
    for (int i = 0; i < n; i++) {
      pii p = {0, 0};
      for (int j = 0; j < m; j++) {
        dp[i][j][dir] = p;  //  不包含自己
        Add(p, grid[i][j]);
      }
    }
  }
  void InitRight(int dir) {
    for (int i = 0; i < n; i++) {
      pii p = {0, 0};
      for (int j = m - 1; j >= 0; j--) {
        dp[i][j][dir] = p;  //  不包含自己
        Add(p, grid[i][j]);
      }
    }
  }
  void InitTop(int dir) {
    for (int j = 0; j < m; j++) {
      pii p = {0, 0};
      for (int i = 0; i < n; i++) {
        Add(p, grid[i][j]);
        dp[i][j][dir] = p;  //  包含自己
      }
    }
  }
  void InitBootom(int dir) {
    for (int j = 0; j < m; j++) {
      pii p = {0, 0};
      for (int i = n - 1; i >= 0; i--) {
        Add(p, grid[i][j]);
        dp[i][j][dir] = p;  //  包含自己
      }
    }
  }

  void Init() {
    n = grid.size();
    m = grid.front().size();
    dp.resize(n, vector<vpii>(m, vector<pii>(4, pii(0, 0))));
    InitLeft(0);
    InitTop(1);
    InitRight(2);
    InitBootom(3);
  }

 public:
  int maxTrailingZeros(vector<vector<int>>& grid_) {
    grid.swap(grid_);

    Init();

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int x = 0; x < 4; x++) {
          for (int y = 0; y < 4; y++) {
            if (x % 2 == y % 2) continue;
            auto& px = dp[i][j][x];
            auto& py = dp[i][j][y];
            pii p = {px.first + py.first, px.second + py.second};
            ans = max(ans, min(p.first, p.second));
          }
        }
      }
    }
    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
