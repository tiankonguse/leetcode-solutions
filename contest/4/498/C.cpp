
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
vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class Solution {
 public:
  vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
    vector<vector<int>> ans(n, vector<int>(m, 0));
    vector<vector<int>> step(n, vector<int>(m, -1));
    queue<tuple<int, int, int>> q;
    for (const auto& s : sources) {
      int r = s[0], c = s[1], color = s[2];
      ans[r][c] = color;
      step[r][c] = 0;
      q.emplace(r, c, 0);
    }
    while (!q.empty()) {
      auto [r, c, time] = q.front();
      const int color = ans[r][c];
      q.pop();
      if (time > step[r][c]) continue;  // 有更优的方案
      for (const auto& [dr, dc] : dirs) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        if (step[nr][nc] == -1) {  // 没有被染色过
          step[nr][nc] = time + 1;
          ans[nr][nc] = color;
          q.emplace(nr, nc, time + 1);
        } else if (step[nr][nc] == time + 1) {  // 同一时间被染色，选择颜色较大的
          ans[nr][nc] = max(ans[nr][nc], color);
        }
      }
    }

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