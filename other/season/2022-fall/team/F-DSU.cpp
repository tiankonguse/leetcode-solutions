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
enum { WATER = 1, EMPTY = 0 };

class Dsu {
  vector<int> fa, score, maxLev;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
      }
    }
  }
  void SetScore(int x, int v) {
    x = Find(x);
    score[x] = max(v, score[x]);
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};

Dsu dsu;

class Solution {
  vector<string> shape;
  int n, m;

  void DfsFillWater(int x, int y, int dir) {
    if (x < 1 || x > n || y < 1 || y > m) return;
    int& ret = grid[dir][x][y];
    if (ret != EMPTY) return;
    ret = WATER;

    char v = shape[x - 1][y - 1];
    if (v == 'l') {
      int d = L[dir];
      grid[d][x][y] = WATER;
      DfsFillWater(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
    } else if (v == 'r') {
      int d = R[dir];
      grid[d][x][y] = WATER;
      DfsFillWater(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
    } else {
      for (int d = 0; d < 4; d++) {
        grid[d][x][y] = WATER;
        DfsFillWater(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
      }
    }
  }

  void FillWater() {
    for (int i = 1; i <= n; i++) {
      DfsFillWater(i, 1, LEFT);
      DfsFillWater(i, m, RIGHT);
    }
    for (int i = 1; i <= m; i++) {
      DfsFillWater(1, i, UP);
      DfsFillWater(n, i, DOWN);
    }
  }

  void DfsFillEmpty(int x, int y, int dir) {
    if (x < 1 || x > n || y < 1 || y > m) return;
    int& ret = grid[dir][x][y];
    if (ret != WATER) return;
    ret = EMPTY;

    char v = shape[x - 1][y - 1];
    if (v == 'l') {
      int d = L[dir];
      grid[d][x][y] = EMPTY;
      if (d != DOWN) {
        DfsFillEmpty(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
      }
    } else if (v == 'r') {
      int d = R[dir];
      grid[d][x][y] = EMPTY;
      if (d != DOWN) {
        DfsFillEmpty(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
      }
    } else {
      for (int d = 0; d < 4; d++) {
        grid[d][x][y] = EMPTY;
        if (d != DOWN) {
          DfsFillEmpty(x + dir4[d][0], y + dir4[d][1], (d + 2) % 4);
        }
      }
    }
  }

  void FillEmpty() {
    for (int i = 1; i <= n; i++) {
      DfsFillEmpty(i, 1, LEFT);
      DfsFillEmpty(i, m, RIGHT);
    }
    for (int i = 1; i <= m; i++) {
      DfsFillEmpty(n, i, DOWN);
    }
  }

  int H(int x, int y, int dir) {
    x--;
    y--;
    return (x * m + y) * 4 + dir;
  }

  void Solver() {
    dsu.Init(n * m * 4 + 1);

    for (int i = n; i >= 1; i--) {
      // 首先预处理，标记每个水的 maxLev，即空气的最高坐标
      for (int j = 1; j <= m; j++) {
        if (grid[DOWN][i][j] == EMPTY && grid[UP][i + 1][j] == WATER) {
          dsu.SetScore(H(i + 1, j, UP), i);
        }
      }

      // 先连通起来
      for (int j = 1; j <= m; j++) {
        char v = shape[i - 1][j - 1];

        if (grid[DOWN][i][j] == WATER && grid[UP][i + 1][j] == WATER) {
          dsu.Union(H(i, j, DOWN), H(i + 1, j, UP));
        }
        if (grid[RIGHT][i][j] == WATER && grid[LEFT][i][j + 1] == WATER) {
          dsu.Union(H(i, j, RIGHT), H(i, j + 1, LEFT));
        }

        if (v == 'l') {
          if (grid[LEFT][i][j] == WATER && grid[DOWN][i][j] == WATER) {
            dsu.Union(H(i, j, LEFT), H(i, j, DOWN));
          }

          if (grid[UP][i][j] == WATER && grid[RIGHT][i][j] == WATER) {
            dsu.Union(H(i, j, UP), H(i, j, RIGHT));
          }
        } else if (v == 'r') {
          if (grid[LEFT][i][j] == WATER && grid[UP][i][j] == WATER) {
            dsu.Union(H(i, j, LEFT), H(i, j, UP));
          }
          if (grid[DOWN][i][j] == WATER && grid[RIGHT][i][j] == WATER) {
            dsu.Union(H(i, j, DOWN), H(i, j, RIGHT));
          }
        } else {
          for (int k = 0; k < 3; k++) {
            if (grid[k][i][j] == WATER && grid[k + 1][i][j] == WATER) {
              dsu.Union(H(i, j, k), H(i, j, k + 1));
            }
          }
        }
      }

      // 当前层如果不满足连通性，则水转化为空气
      for (int j = 1; j <= m; j++) {
        if (grid[DOWN][i][j] == WATER && dsu.GetScore(H(i, j, DOWN)) >= i) {
          DfsFillEmpty(i, j, DOWN);
        }
      }
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

    Solver();

    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 0; k < 4; k++) {
          if (grid[k][i][j] == WATER) {
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
