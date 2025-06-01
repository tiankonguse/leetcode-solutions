
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
int dp[21][21][51][1025];
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  vector<string> classroom;
  map<pair<int, int>, int> xyIndex;
  vector<pair<int, int>> xys;
  int ans;
  int E;
  int n, m;
  void Dfs(int x, int y, int energy, const int mask, int step) {  //
    if (energy < 0) return;
    if (mask == 0) {
      ans = min(ans, step);
      return;
    }
    if (dp[x][y][energy][mask] != -1) {
      return;
    }
    dp[x][y][energy][mask] = step;
    if (classroom[x][y] == 'R' && energy < E) {
      Dfs(x, y, E, mask, step);
      return;
    }

    // 判断是不是 mask 中的点
    int newMask = mask;
    if (xyIndex.count({x, y})) {
      int index = xyIndex[{x, y}];
      if (newMask & (1 << index)) {
        newMask ^= (1 << index);
      }
      if (newMask == 0) {
        ans = min(ans, step);
        return;
      }
    }

    for (auto [dx, dy] : dir4) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        continue;
      }
      if (classroom[nx][ny] == 'X') {
        continue;
      }
      Dfs(nx, ny, energy - 1, newMask, step + 1);
    }
  }

 public:
  int minMoves(vector<string>& classroom_, int energy) {
    E = energy;
    classroom.swap(classroom_);
    n = classroom.size();
    m = classroom[0].size();
    int maskNum = 0;
    int sx = 0, sy = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (classroom[i][j] == 'S') {
          classroom[i][j] = '.';
          sx = i, sy = j;
        } else if (classroom[i][j] == 'L') {
          xys.push_back({i, j});
          xyIndex[{i, j}] = maskNum;
          maskNum++;
        }
      }
    }
    memset(dp, -1, sizeof(dp));
    ans = INT_MAX;
    Dfs(sx, sy, energy, (1 << maskNum) - 1, 0);
    if (ans == INT_MAX) {
      return -1;
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