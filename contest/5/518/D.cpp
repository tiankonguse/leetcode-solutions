
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 882 / 1001 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int flag[80][80][80][4];
enum Dir { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };
int Next[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
class Solution {
 public:
  int minCost(vector<vector<int>>& grid, const int K) {
    int n = grid.size();
    int m = grid[0].size();
    memset(flag, -1, sizeof(flag));
    min_queue<tuple<int, int, int, int, int>> que;  // <cost, x, y, k, dir>
    int ans = INT_MAX;
    auto Add = [&](int cost, int x, int y, int k, int dir) {
      if (x < 0 || x >= n || y < 0 || y >= m || k > K) return;
      int& ret = flag[x][y][k][dir];
      cost += grid[x][y];
      if (ret != -1 && ret <= cost) return;
      ret = cost;
      que.push(make_tuple(ret, x, y, k, dir));
      if (x == n - 1 && y == m - 1) ans = min(ans, ret);
    };

    for (int i = 0; i < 4; i++) {
      Add(0, 0, 0, 0, i);
    }
    while (!que.empty()) {
      auto [cost, x, y, k, dir] = que.top();
      que.pop();
      for (int i = 0; i < 4; i++) {
        Add(cost, x + Next[i][0], y + Next[i][1], k + (i != dir), i);
      }
    }
    if (ans == INT_MAX) ans = -1;
    return ans;
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