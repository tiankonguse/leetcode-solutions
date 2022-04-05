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

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 1;
    }
  }

  int Score(int x) { return score[Find(x)]; }

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
    if (x < y) {
      fa[y] = x;
      score[x] += score[y];
    } else if (x > y) {
      fa[x] = y;
      score[y] += score[x];
    }
  }
};

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  int n, m;
  int Index(int x, int y) { return x * m + y; }

 public:
  int largestIsland(vector<vector<int>>& grid) {
    n = grid.size();
    m = grid[0].size();
    int ans = 0;

    Dsu dsu;
    dsu.Init(n * m);

    rep(x, n) {
      rep(y, m) {
        if (grid[x][y] == 0) continue;
        rep(i, 4) {
          int X = x + dir4[i][0];
          int Y = y + dir4[i][1];
          if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
          if (grid[X][Y] == 0) continue;
          dsu.Union(Index(x, y), Index(X, Y));
        }
      }
    }

    rep(x, n) {
      rep(y, m) {  //
        set<int> roots;
        roots.insert(dsu.Find(Index(x, y)));
        rep(i, 4) {
          int X = x + dir4[i][0];
          int Y = y + dir4[i][1];
          if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
          if (grid[X][Y] == 0) continue;
          roots.insert(dsu.Find(Index(X, Y)));
        }

        int tmp = 0;
        for (auto r : roots) {
          tmp += dsu.Score(r);
        }
        chmax(ans, tmp);
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
