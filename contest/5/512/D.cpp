
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
  vector<vector<vector<ll>>> dp;
  vector<vector<int>> penalty;
  int m, n;

  ll CostXY(ll x, ll y) {  //
    return (x + 1) * (y + 1);
  }

 public:
  long long minCost(int m_, int n_, vector<vector<int>>& penalty_) {  //
    m = m_;
    n = n_;
    penalty.swap(penalty_);
    dp.assign(m, vector<vector<ll>>(n, vector<ll>(2, -1)));
    min_queue<tuple<ll, int, int, int>> que;  // <cost, x, y, flag>
    auto Add = [&](const ll cost, int x, int y, int flag) {
      ll& ret = dp[x][y][flag];
      if (ret == -1 || ret > cost) {
        ret = cost;
        que.push({cost, x, y, flag});
      }
    };
    Add(CostXY(0, 0), 0, 0, 0);
    while (!que.empty()) {
      const auto [cost, x, y, flag] = que.top();
      MyPrintf("cost=%lld, x=%d, y=%d, flag=%d\n", cost, x, y, flag);
      que.pop();
      if (x == m - 1 && y == n - 1) return cost;
      const int nextFlag = 1 - flag;
      // 等待
      Add(cost + penalty[x][y], x, y, nextFlag);
      // 上下左右
      for (int i = 0; i < 4; i++) {
        const int X = x + dir4[i][0];
        const int Y = y + dir4[i][1];
        if (X < 0 || X >= m || Y < 0 || Y >= n) continue;
        if (i % 2 != nextFlag) {
          Add(cost + CostXY(X, Y), X, Y, nextFlag);
        } else {
          Add(cost + CostXY(X, Y) + penalty[x][y], X, Y, nextFlag);
        }
      }
    }
    return 0;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif