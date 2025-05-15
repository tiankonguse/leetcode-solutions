
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  bool canPartitionGrid(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<ll> row(n, 0);
    vector<ll> col(m, 0);
    ll sum = 0;
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < m; ++j) {
    row[i] += grid[i][j];
    col[j] += grid[i][j];
    sum += grid[i][j];
  }
}
for (int i = 1; i < n; ++i) {
  if (sum % 2 == 0 && row[i - 1] == sum / 2) return true;
  row[i] += row[i - 1];
}
for (int j = 1; j < m; ++j) {
  if (sum % 2 == 0 && col[j - 1] == sum / 2) return true;
  col[j] += col[j - 1];
}
    if (n == 1 && m == 2) return false;
    if (n == 2 && m == 1) return false;

    auto Check = [sum](const vector<ll>& row, const ll x, const ll v, const int y, const int m) {
      int n = row.size();
      if (n == 1) return false;
      ll newSum = sum - v;
      if (newSum % 2 != 0) return false;
      ll target = newSum / 2;
      // 定义： row 是一个升序数组，第 x 行需要减去 v， 选择分割线 limit，使得 sum[0, limit] = sum[limit+1, n-1]

// 分割线 limit 在 x 之前 [0, x)，即前缀和不需要减去 v，此时 row[limit] == target
if (x - 1 >= 0 && row[x - 1] >= target) {  // 肯定可以查找到
  auto limit = lower_bound(row.begin(), row.end() + x, target) - row.begin();
  if (row[limit] == target) {
    if (m >= 2 && n - limit > 2) return true;                   // 至少两行两列中删除，必然联通
    if (m == 1 && (limit + 1 == x || x + 1 == n)) return true;  // 只有一列，删除的元素在分割线的两侧
    if (n - limit == 2 && (y == 0 || y + 1 == m)) return true;  // 只有一行，删除的元素在分割线的两侧
  }
}

// 分割线 limit 在 x 之后 [x, n)，则需要 row[limit] - v == target
if (x < n - 1 && row[x] - v <= target) {
  auto limit = lower_bound(row.begin() + x, row.end(), target + v) - row.begin();
  if (row[limit] == target + v) {
    if (m >= 2 && limit + 1 >= 2) return true;              // 至少两行两列中删除，必然联通
    if (m == 1 && (x == 0 || x + 1 == limit)) return true;              // 只有一列，删除的元素在分割线的两侧
    if (limit == 0 && (y == 0 || y + 1 == m)) return true;  // 只有一行，删除的元素在分割线的两侧
  }
}

      return false;
    };

    // 尝试删除一个元素
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ll v = grid[i][j];
        if (Check(row, i, v, j, m)) return true;
        if (Check(col, j, v, i, n)) return true;
      }
    }

    return false;
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