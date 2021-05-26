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

int dp[max3][max3];  // 0 少一步，1 相等，2 多一步

class Solution {
 public:
  bool canCross(vector<int>& stones) {
    int n = stones.size();

    if (stones[1] != 1) {
      return false;
    }
    if (n == 2) {
      return true;
    }

    memset(dp, 0, sizeof(dp));

    unordered_map<ll, int> m;
    for (int i = 0; i < n; i++) {
      m[stones[i]] = i;
    }

    queue<pair<int, int>> que;
    que.push({0, 1});
    dp[0][1] = 1;

    while (!que.empty()) {
      auto p = que.front();
      que.pop();

      ll dis = stones[p.second] - stones[p.first];
      int from = p.second;

      for (ll i = max(1LL, dis - 1); i <= dis + 1; i++) {
        ll val = stones[from] + i;
        if (m.count(val) == 0) continue;
        int to = m[val];

        if (dp[from][to] == 1) continue;

        if (to + 1 == n) {
          return true;
        }

        dp[from][to] = 1;
        que.push({from, to});
      }
    }

    return false;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
