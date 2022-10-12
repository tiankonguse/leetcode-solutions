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
// LONG_MIN, LONG_MAX

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

// 1 水， 2 空气
int grid[4][55][55];
int dir4[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
int L[4] = {3, 2, 1, 0};
int R[4] = {1, 0, 3, 2};

enum { LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3 };
enum { EMPTY = -1, WATER = 0 };

class Solution {
  vector<string> shape;
  int n, m;

  void Dfs(int x, int y, int dir, int maxLev) {
    if (x < 1 || x > n || y < 1 || y > m) return;
    int& ret = grid[dir][x][y];

    if (maxLev == -1) {
      if (ret != EMPTY) return;
      ret = WATER;
    } else {
      if (ret == EMPTY) return;   // 已经是空气了
      if (ret >= maxLev) return;  // 没有更低的海拔

      if (x <= maxLev) {
        ret = EMPTY;
        maxLev = x;
      } else {
        ret = maxLev;
      }
    }

    char v = shape[x - 1][y - 1];
    if (v == 'l') {
      int d = L[dir];
      Dfs(x, y, d, maxLev);
      Dfs(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4, maxLev);
    } else if (v == 'r') {
      int d = R[dir];
      Dfs(x, y, d, maxLev);
      Dfs(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4, maxLev);
    } else {
      for (int d = 0; d < 4; d++) {
        Dfs(x, y, d, maxLev);
        Dfs(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4, maxLev);
      }
    }
  }

  void FillWater() {
    for (int i = 1; i <= n; i++) {
      Dfs(i, 1, LEFT, -1);
      Dfs(i, m, RIGHT, -1);
    }
    for (int i = 1; i <= m; i++) {
      Dfs(1, i, UP, -1);
      Dfs(n, i, DOWN, -1);
    }
  }

  void FillEmpty() {
    for (int i = n; i >= 1; i--) {
      Dfs(i, 1, LEFT, i);
      Dfs(i, m, RIGHT, i);
    }
    for (int i = 1; i <= m; i++) {
      Dfs(n, i, DOWN, n);
    }
  }

 public:
  int reservoir(vector<string>& shape_) {
    shape.swap(shape_);
    n = shape.size();
    m = shape.back().size();

    memset(grid, EMPTY, sizeof(grid));
    FillWater();
    FillEmpty();

    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 0; k < 4; k++) {
          if (grid[k][i][j] != EMPTY) {
            ans++;
          }
        }
      }
    }
    return ans / 2;
  }
};

/*
["....rl","l.lr.r",".l..r.","..lr.."]
[".rlrlrlrl","ll..rl..r",".llrrllrr","..lr..lr."]
["rlrr","llrl","llr."]
["...rl...","..r..l..",".r.rl.l.","r.r..l.l","l.l..rl.",".l.lr.r.","..l..r..","...lr..."]
*/

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
