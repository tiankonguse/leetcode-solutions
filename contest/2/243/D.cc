#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

double dp[1111][1111];  // dp(i, j) 前i 个跳过 j
                        // 个的最短时间(最后一次不向上取整)

class Solution {
  ll speed;
  ll hoursBefore;
  int n;
  vector<int> dist;

  ll DIV(ll a, ll b) { return a; }
  ll FIX(ll a) { return (a + speed - 1) / speed * speed; }

  // dp[m][k] 前  m 个跳过 K 次的最短时间(向上取整)
  ll DFS(int m, int k) {
    if (dp[m][k] != 0) {
      return dp[m][k];
    }

    if (m == 1) {
      return dp[m][k] = DIV(dist[m - 1], speed);
    }

    if (k == m - 1) {  // 全部跳过
      ll ans = DFS(m - 1, k - 1) + DIV(dist[m - 1], speed);
      return dp[m][k] = ans;
    }

    if (k == 0) {  // 都不不跳过，前一个需要向上取整
      ll ans = FIX(DFS(m - 1, 0)) + DIV(dist[m - 1], speed);
      return dp[m][k] = ans;
    }

    // 选择跳过 或者 不跳过
    ll ans_yes_skip = DFS(m - 1, k - 1) + DIV(dist[m - 1], speed);
    ll ans_no_skip = FIX(DFS(m - 1, k)) + DIV(dist[m - 1], speed);

    // printf("m=%d k=%d t=%lld\n", m, k, ans);
    return dp[m][k] = min(ans_yes_skip, ans_no_skip);
  }

  bool Check(int k) {
    if (DFS(n, k) <= hoursBefore * speed) {
      return true;
    } else {
      return false;
    }
  }

 public:
  int minSkips(vector<int>& dist_, int speed_, int hoursBefore_) {
    dist.swap(dist_);
    speed = speed_;
    hoursBefore = hoursBefore_;

    n = dist.size();
    memset(dp, 0, sizeof(dp));

    // 全跳过有答案，求最小值
    int left = 0, right = n;
    while (left < right) {
      int mid = (left + right) / 2;
      if (Check(mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return right == n ? -1 : right;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
