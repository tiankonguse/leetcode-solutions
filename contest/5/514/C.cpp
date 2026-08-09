
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
  vector<vector<int>> mat;
  int n, m;

  int Sum() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        sum += mat[i][j];
      }
    }
    return sum;
  }
  vector<vector<int>> cols;         // 每个位置向上连续1的个数
  vector<vector<int>> rows;         // 每个位置向左连续1的个数
  vector<vector<int>> dpRightDown;  // 每个位置为右下角的最大正方形的边长
  vector<vector<int>> dpRightUp;    // 每个位置为右上角的最大正方形的边长
  vector<vector<int>> dpLeftDown;   // 每个位置为左下角的最大正方形的边长
  vector<vector<int>> dpLeftUp;     // 每个位置为左上角的最大正方形的边长
  void Init() {
    cols.assign(n, vector<int>(m, 0));
    rows.assign(n, vector<int>(m, 0));
    dpRightDown.assign(n, vector<int>(m, 0));
    dpRightUp.assign(n, vector<int>(m, 0));
    dpLeftDown.assign(n, vector<int>(m, 0));
    dpLeftUp.assign(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int v = mat[i][j];
        if (v == 0) continue;
        cols[i][j] = j == 0 ? v : cols[i][j - 1] + v;
        rows[i][j] = i == 0 ? v : rows[i - 1][j] + v;
        dpRightDown[i][j] = 1;
        if (i > 0 && j > 0) {
          dpRightDown[i][j] = min(dpRightDown[i - 1][j - 1], min(cols[i][j - 1], rows[i - 1][j])) + 1;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        // 根据 dpRightDown 计算出其他的值
        if (dpRightDown[i][j] == 0) continue;
        const int D = i;
        const int R = j;
        const int L = R - dpRightDown[i][j] + 1;
        const int U = D - dpRightDown[i][j] + 1;
        dpRightUp[U][R] = max(dpRightUp[U][R], dpRightDown[i][j]);
        dpLeftUp[U][L] = max(dpLeftUp[U][L], dpRightDown[i][j]);
        dpLeftDown[D][L] = max(dpLeftDown[D][L], dpRightDown[i][j]);
      }
    }
  }

  int GetRightDown(int maxDown, int maxRight) {
    int ans = 0;
    for (int i = 0; i <= maxDown; i++) {
      for (int j = 0; j <= maxRight; j++) {
        ans = max(ans, dpRightDown[i][j]);
      }
    }
    return ans;
  }
  int GetLeftUp(int minUp, int minLeft) {
    int ans = 0;
    for (int i = minUp; i <= n - 1; i++) {
      for (int j = minLeft; j <= m - 1; j++) {
        ans = max(ans, dpLeftUp[i][j]);
      }
    }
    return ans;
  }

 public:
  int maxArea(vector<vector<int>>& mat_) {
    mat.swap(mat_);
    n = mat.size();
    m = mat[0].size();
    if (Sum() <= 1) return 0;
    Init();

    int ans = 0;
    // 枚举水平分割线
    for (int ni = 1; ni < n; ni++) {  // [0, ni) [ni, n)
      int tmp = min(GetRightDown(ni - 1, m - 1), GetLeftUp(ni, 0));
      ans = max(ans, tmp);
    }
    // 枚举垂直分割线
    for (int mi = 0; mi < m; mi++) {  // [0, mi) [mi, m)
      int tmp = min(GetRightDown(n - 1, mi - 1), GetLeftUp(0, mi));
      ans = max(ans, tmp);
    }

    return ans * ans;
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