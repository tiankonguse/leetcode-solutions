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
  int n, m;
  int treeNum = 0;
  map<int, pair<int, int>> treeInfo;
  vector<vector<int>> g;
  vector<vector<int>> nums;

  vector<vector<int>> flag;

  int Dfs(int x, int y) {
    if (flag[x][y]) return 0;
    flag[x][y] = 1;
    if (nums[x][y] < 0) return 0;
    int ans = 0;
    if (nums[x][y]) ans++;
    for (int k = 0; k < 4; k++) {
      int X = x + dir4[k][0];
      int Y = y + dir4[k][1];
      if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
      ans += Dfs(X, Y);
    }
    return ans;
  }

  int Dis(int x, int y, int XX, int YY) {
    flag.clear();
    flag.resize(n, vector<int>(m, 0));
    queue<tuple<int, int, int>> que;
    que.push({0, x, y});
    flag[x][y] = 1;

    while (!que.empty()) {
      auto [step, x, y] = que.front();
      que.pop();
      for (int k = 0; k < 4; k++) {
        int X = x + dir4[k][0];
        int Y = y + dir4[k][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
        if (nums[X][Y] < 0) continue;
        if (flag[X][Y]) continue;
        if (X == XX && Y == YY) return step + 1;
        que.push({step + 1, X, Y});
        flag[X][Y] = 1;
      }
    }
    return 0;
  }

 public:
  int cutOffTree(vector<vector<int>>& nums_) {
    nums.swap(nums_);
    if (nums[0][0] == 0) return -1;

    n = nums.size();
    m = nums.front().size();
    vector<tuple<int, int, int>> tree;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int& v = nums[i][j];
        v--;
        if (v > 0) {
          tree.push_back({v, i, j});
        }
      }
    }

    flag.resize(n, vector<int>(m, 0));
    int c = Dfs(0, 0);
    printf("c=%d %d\n", c, tree.size());
    if (c != tree.size()) {
      return -1;
    }

    int ans = 0;
    int x = 0, y = 0;
    sort(tree.begin(), tree.end());
    for (auto [v, X, Y] : tree) {
      if (x == X && y == Y) continue;
      ans += Dis(x, y, X, Y);
      x = X, y = Y;
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
