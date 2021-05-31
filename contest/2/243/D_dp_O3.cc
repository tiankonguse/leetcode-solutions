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

ll dp[1111][1111];
ll sum[1111];

class Solution {
  ll speed;
  ll hoursBefore;
  int n;
  vector<int> dist;

  void Init() {
    n = dist.size();
    memset(dp, 0, sizeof(dp));

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + dist[i - 1];
    }
  }

  ll DIV(ll a, ll b) { return (a + b - 1) / b; }

  // dp[m][k] 前  m 个休息 k 次的最短时间(向上取整)
  ll DFS(int m, int k) {
    if (dp[m][k] != 0) {
      return dp[m][k];
    }

    if (k == 0) {
      ll ans = DIV(sum[m], speed);
      // printf("m=%d k=%d t=%lld\n", m, k, ans);
      return dp[m][k] = ans;
    }

    ll ans = DFS(m - 1, k - 1) + DIV(dist[m - 1], speed);
    for (int i = k; i < m; i++) {
      ll tmp = DFS(i, k - 1) + DIV(sum[m] - sum[i], speed);
      // printf("i=%d dfs=%lld DIV=%lld\n", i, DFS(i, k-1), DIV(sum[m] - sum[i],
      // speed)); printf("m=%d k=%d i=%d t=%lld\n", m, k, i, tmp);
      ans = min(tmp, ans);
    }
    // printf("m=%d k=%d t=%lld\n", m, k, ans);
    return dp[m][k] = ans;
  }

  // 跳过 k 次，则休息 n-1 - k 次
  bool Check(int k) {
    int max_sleep = n - 1;
    if (DFS(n, max_sleep - k) <= hoursBefore) {
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

    Init();

    if (DIV(sum[n], speed) > hoursBefore) {
      return -1;
    }

    int left = 0, right = n - 1;
    while (left < right) {
      int mid = (left + right) / 2;
      if (Check(mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
      // printf("left=%d right=%d\n", left, right);
    }
    return right;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
