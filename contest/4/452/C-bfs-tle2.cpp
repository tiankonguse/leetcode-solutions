
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
int dp1[21][21][1025];
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  vector<string> classroom;
  map<pair<int, int>, int> xyIndex;
  vector<pair<int, int>> xys;
  int ans;
  int E;
  int n, m;

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
    if (maskNum == 0) {
      return 0;
    }
    memset(dp, -1, sizeof(dp));
    memset(dp1, -1, sizeof(dp1));
    ans = INT_MAX;
    queue<tuple<int, int, int, int>> que;

    auto Add = [&](int x, int y, int energy, const int mask, int step) {
      if (dp[x][y][energy][mask] != -1) {
        return;
      }
      if (dp1[x][y][mask] != -1 && dp1[x][y][mask] >= energy) {
        return;
      }
      dp1[x][y][mask] = energy;
      dp[x][y][energy][mask] = step;
      que.push({x, y, energy, mask});
    };
    Add(sx, sy, energy, (1 << maskNum) - 1, 0);
    while (!que.empty()) {
      const auto [x, y, energy, mask] = que.front();
      que.pop();
      const int step = dp[x][y][energy][mask];
      for (auto [dx, dy] : dir4) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
          continue;
        }
        if (classroom[nx][ny] == 'X') {
          continue;
        }
        int newEnergy = energy - 1;
        int newStep = step + 1;
        int newMask = mask;
        if (classroom[nx][ny] == 'R') {
          newEnergy = E;
        } else if (classroom[nx][ny] == 'L') {
          int index = xyIndex[{nx, ny}];
          if (newMask & (1 << index)) {
            newMask ^= (1 << index);
          }
          if (newMask == 0) {
            return newStep;
          }
        }
        if (newEnergy > 0) {
          Add(nx, ny, newEnergy, newMask, newStep);
        }
      }
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