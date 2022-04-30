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

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  vector<vector<int>> g;  // 0 太平洋， 1~N 岛屿， N+1 大西洋
  int n, m;
  int N;

  int H(int x, int y) { return 1 + x * m + y; }

  void Build(vector<vector<int>>& heights) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int uu = heights[i][j];
        int u = H(i, j);

        if (i == 0 || j == 0) {  // 与太平洋相连
          g[0].push_back(u);
        }
        if (i == n - 1 || j == m - 1) {  // 与大西洋相连
          g[N + 1].push_back(u);
        }

        for (int k = 0; k < 4; k++) {
          int x = i + dir4[k][0];
          int y = j + dir4[k][1];
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          int vv = heights[x][y];
          int v = H(x, y);
          if (vv >= uu) {
            g[u].push_back(v);
          }
        }
      }
    }
  }

  map<int, int> nums;  // 到达计数
  void Solver(int x) {
    vector<int> flag(N + 2, 0);
    queue<int> que;
    que.push(x);
    flag[x] = 1;

    while (!que.empty()) {
      int u = que.front();
      que.pop();

      for (int v : g[u]) {
        if (flag[v]) continue;
        que.push(v);
        flag[v] = 1;
        nums[v]++;
      }
    }
  }

 public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    n = heights.size();
    m = heights.front().size();
    N = n * m;
    g.resize(N + 2);
    Build(heights);
    Solver(0);
    Solver(N + 1);

    vector<vector<int>> ans;
    for (auto [u, num] : nums) {
      if (num == 2) {
        int v = u - 1;
        ans.push_back({v / m, v % m});
      }
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
