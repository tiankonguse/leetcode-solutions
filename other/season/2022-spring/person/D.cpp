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

int dp[111][33][33];

// __builtin_popcount
class Solution {
  vector<vector<int>> nums;
  int n;
  int m;
  int FULL;

  // 0~1 empty, 1~n+1 board
  // mask : 1 代表未选择
  int Dfs(const int x, const int mask1, const int mask2) {
    int& ret = dp[x][mask1][mask2];
    if (ret != -1) return ret;
    if (x == 0 && mask2 == 0) return ret = 0;  // 出口
    if (mask2 == 0) return ret = Dfs(x - 1, FULL, mask1);

    ret = n * 10;  // 最大值

    for (int i = 0; i < m; i++) {
      if (((mask2 >> i) & 1) == 0) continue;

      if (nums[x + 2][i] == 0) {  // 尝试不覆盖，条件是这个时间点没有陨石
        int tmp = Dfs(x, mask1, mask2 ^ (1 << i));
        if (tmp < ret) ret = tmp;
      }

      int maski2 = mask2;
      for (int j = i; j < m; j++) {  // 单屏障，尝试从 i 开到 j
        if (((maski2 >> j) & 1) == 0) break;  // 不能覆盖
        maski2 ^= (1 << j);
        int tmp = (j - i) + 2 + Dfs(x, mask1, maski2);
        if (tmp < ret) ret = tmp;
      }

      maski2 = mask2;                // 表层
      int maski1 = mask1;            // 下层
      for (int j = i; j < m; j++) {  // 联合屏障，尝试从 i 开到 j
        if (((maski1 >> j) & 1) == 0) break;  // 不能覆盖
        if (((maski2 >> j) & 1) == 0) break;  // 不能覆盖
        maski1 ^= (1 << j);
        maski2 ^= (1 << j);

        int tmp = (j - i) + 3 + Dfs(x, maski1, maski2);
        if (tmp < ret) ret = tmp;
      }
    }
    return ret;
  }

 public:
  int defendSpaceCity(vector<int>& time, vector<int>& position) {
    memset(dp, -1, sizeof(dp));
    n = 1;
    for (auto& p : position) {
      p += 2;
      n = max(n, p);
    }
    m = 1;
    for (auto& t : time) {
      m = max(m, t);
      t--;
    }
    nums.resize(n + 2, vector<int>(m, 0));
    for (int i = 0; i < time.size(); i++) {
      int x = position[i];
      int y = time[i];
      nums[x][y] = 1;
      // printf("x=%d y=%d \n", x, y);
    }

    FULL = (1 << m) - 1;
    // printf("FULL=%d n=%d m=%d\n", FULL, n, m);
    return Dfs(n - 2, FULL, FULL);
  }
};

int main() {
  int ans;
  vi times;
  vi pos;

  ans = 5;
  times = {1, 2, 1};
  pos = {6, 3, 3};
  TEST_SMP2(Solution, defendSpaceCity, ans, times, pos);

  ans = 9;
  times = {1, 1, 1, 2, 2, 3, 5};
  pos = {1, 2, 3, 1, 2, 1, 3};
  TEST_SMP2(Solution, defendSpaceCity, ans, times, pos);

  return 0;
}
