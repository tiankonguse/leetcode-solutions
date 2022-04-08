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

int dir2[2][2] = {{0, 1}, {1, 0}};
int rdir2[2][2] = {{0, -1}, {-1, 0}};
class Solution {
  vector<vector<int>> nums;
  vector<vector<int>> dp;
  int n, m;
  bool Solver() {
    dp.resize(n, vector<int>(m, -1));

    queue<pair<int, int>> que;
    que.push({n - 1, m - 1});
    dp[n - 1][m - 1] = 0;
    if (n == 1 && m == 1) return true;

    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      for (int i = 0; i < 2; i++) {
        int X = x + rdir2[i][0];
        int Y = y + rdir2[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) {
          continue;
        }
        if (dp[X][Y] != -1 || nums[X][Y] == 1) continue;
        dp[X][Y] = dp[x][y] + 1;
        if (X == 0 && Y == 0) return true;
        que.push({X, Y});
      }
    }

    return false;
  }

 public:
  vector<vector<int>> pathWithObstacles(vector<vector<int>>& nums_) {
    vector<vector<int>> ans;
    nums.swap(nums_);
    if (nums.front().front() || nums.back().back()) return ans;
    n = nums.size();
    m = nums.front().size();
    if (!Solver()) {
      return ans;
    }

    int x = 0, y = 0;
    while (x != n - 1 || y != m - 1) {
      ans.push_back({x, y});

      for (int i = 0; i < 2; i++) {
        int X = x + dir2[i][0];
        int Y = y + dir2[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) {
          continue;
        }
        if (dp[X][Y] + 1 == dp[x][y]) {
          x = X;
          y = Y;
          break;
        }
      }
    }
    ans.push_back({x, y});

    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
