#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
int a[101][101];
int dp[101][101];
int max_sum(int i, int j) {
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  if (i == n - 1) {  // 最底层
    return dp[i][j] = a[i][j];
  } else {
    return dp[i][j] = a[i][j] + max(max_sum(i + 1, j), max_sum(i + 1, j + 1));
  }
}
int Solver() { 
    memset(dp, -1, sizeof(dp)); 
    return max_sum(0, 0);
}

// 使用递归无记忆化计算最短路径和
int dfs(const vector<vector<int>> &triangle, int row, int col) {
  if (row == triangle.size() - 1) {  // 到达最后一行
    return triangle[row][col];
  }
  int sum1 = dfs(triangle, row + 1, col);
  int sum2 = dfs(triangle, row + 1, col + 1);
  return triangle[row][col] + min(sum1, sum2);
}

int minimumTotal(const vector<vector<int>> &triangle) {
  if (triangle.empty()) return 0;
  return dfs(triangle, 0, 0);
}

int main() {
  // 示例测试用例
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};

  cout << "最短路径和为: " << minimumTotal(triangle) << endl;
  return 0;
}

// f(1) = 1 = 2^0
// f(2) = 2 * f(1) = 2^1
// f(3) = 2 * f(2) = 2^2
// f(4) = 2 * f(3) = 2^3
// ...
// f(n) = 2 * f(n-1) = 2^(n-1)