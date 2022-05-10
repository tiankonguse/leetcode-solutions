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
void chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
}
template <class T>
void chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
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
int dir4[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};
typedef pair<int, int> pii;
int dp[2][8][8][8][8];

class Solution {
  const int CatWin = 0;
  const int mouseWin = 1;
  vector<string> grid;
  int n, m;
  int catJump;
  int mouseJump;

  pii Find(char c) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == c) {
          return {i, j};
        }
      }
    }
    return {0, 0};
  }

  bool IsConnect(pii s) {
    set<pii> h;

    queue<pii> que;
    h.insert(s);
    que.push(s);

    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
        if (grid[X][Y] == 'F') return true;
        if (grid[X][Y] == '#') continue;
        pii t = {X, Y};
        if (h.count(t)) continue;
        h.insert(t);
        que.push(t);
      }
    }

    return false;
  }

  int Dfscat(const pii cat, const pii mouse) {
    auto [x, y] = cat;
    int& ret = dp[CatWin][mouse.first][mouse.second][x][y];
    if (ret != -1) return ret;
    ret = -2;  // 搜索中

    for (int i = 0; i < 5; i++) {
      for (int k = 1; k <= catJump; k++) {
        int X = x + dir4[i][0] * k;
        int Y = y + dir4[i][1] * k;
        if (X < 0 || X >= n || Y < 0 || Y >= m) break;
        if (grid[X][Y] == '#') break;
        if (grid[X][Y] == 'F') {
          // printf("cat move cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
          //        cat.second, mouse.first, mouse.second, CatWin);
          return ret = CatWin;
        }

        pii pos = {X, Y};
        if (pos == mouse) {
          // printf("cat move cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
          //        cat.second, mouse.first, mouse.second, CatWin);
          return ret = CatWin;
        }

        if (DfsMouse(mouse, pos) == CatWin) {
          // printf("cat move cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
          //        cat.second, mouse.first, mouse.second, CatWin);
          return CatWin;
        }
      }
    }

    // printf("step=%d cat move cat[%d %d] mouse[%d %d] ret=%d\n", step,
    // cat.first,
    //        cat.second, mouse.first, mouse.second, mouseWin);
    return ret = mouseWin;
  }

  int DfsMouse(const pii mouse, const pii cat) {
    auto [x, y] = mouse;
    int& ret = dp[mouseWin][x][y][cat.first][cat.second];
    if (ret != -1) return ret;
    ret = -2;  // 搜索中

    for (int i = 0; i < 5; i++) {
      for (int k = 1; k <= mouseJump; k++) {
        int X = x + dir4[i][0] * k;
        int Y = y + dir4[i][1] * k;
        if (X < 0 || X >= n || Y < 0 || Y >= m) break;
        if (grid[X][Y] == '#') break;
        if (grid[X][Y] == 'F') {
          printf("cat mouse cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
                 cat.second, mouse.first, mouse.second, mouseWin);
          return ret = mouseWin;
        }

        pii pos = {X, Y};
        if (pos == cat) continue;  // 不能到达猫的位置

        if (Dfscat(cat, pos) == mouseWin) {
          printf("cat mouse cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
                 cat.second, mouse.first, mouse.second, mouseWin);
          return ret = mouseWin;
        }
      }
    }
    if (x == 1) {
      printf("cat mouse cat[%d %d] mouse[%d %d] ret=%d\n", cat.first,
             cat.second, mouse.first, mouse.second, CatWin);
    }
    return ret = CatWin;
  }

 public:
  bool canMouseWin(vector<string>& grid_, int catJump_, int mouseJump_) {
    grid.swap(grid_);
    catJump = catJump_;
    mouseJump = mouseJump_;
    n = grid.size();
    m = grid.front().size();
    pii cat = Find('C');
    pii mouse = Find('M');
    int catFlag = IsConnect(cat);
    int mouseFlag = IsConnect(mouse);
    if (!mouseFlag) return CatWin;
    if (!catFlag) return mouseWin;

    memset(dp, -1, sizeof(dp));

    return DfsMouse(mouse, cat);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
