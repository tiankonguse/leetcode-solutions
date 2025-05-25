
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
  int minMoves(vector<string>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    if (n == 1 && m == 1) return 0;
    if (matrix.back().back() == '#') return -1;
    map<char, vector<pair<int, int>>> portal;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char c = matrix[i][j];
        if (c == '.') continue;
        if (c == '#') continue;
        portal[c].push_back({i, j});
      }
    }

    queue<tuple<int, int, int>> q;
    auto Add = [&](int x, int y, int step) {
      if (x < 0 || x >= n || y < 0 || y >= m || matrix[x][y] == '#') return;
      char oldVal = matrix[x][y];
      if (oldVal == '.') {
        q.push({x, y, step});
        matrix[x][y] = '#';
      } else {
        // 不消耗到达所有相连的位置
        // TODO: 题目不确定第一次到达时是不是必须传送
        for (auto [x, y] : portal[oldVal]) {
          if (x < 0 || x >= n || y < 0 || y >= m || matrix[x][y] == '#') continue;
          q.push({x, y, step});
          matrix[x][y] = '#';
        }
      }
    };
    Add(0, 0, 0);
    while (!q.empty()) {
      auto [x, y, step] = q.front();
      q.pop();
      if (x == n - 1 && y == m - 1) return step;
      Add(x + 1, y, step + 1);
      Add(x - 1, y, step + 1);
      Add(x, y + 1, step + 1);
      Add(x, y - 1, step + 1);
    }
    return -1;
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