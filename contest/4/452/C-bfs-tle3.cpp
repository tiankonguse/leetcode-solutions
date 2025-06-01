
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
int minPath[21][21][21][21];

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
  vector<string> classroom;
  map<pair<int, int>, int> xyIndex;
  vector<pair<int, int>> xys;
  int ans;
  int E;
  int n, m;
  void InitPath() {
    memset(minPath, -1, sizeof(minPath));
    for (auto [sx, sy] : targets) {
      queue<pair<int, int>> que;
      que.push({sx, sy});
      minPath[sx][sy][sx][sy] = 0;

      while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        const int step = minPath[sx][sy][x][y] + 1;
        for (auto [dx, dy] : dir4) {
          int nx = x + dx;
          int ny = y + dy;
          if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            continue;
          }
          if (classroom[nx][ny] == 'X') {
            continue;
          }
          if (minPath[sx][sy][nx][ny] == -1) {
            minPath[sx][sy][nx][ny] = step;
            que.push({nx, ny});
          }
        }
      }
    }
  }
  vector<pair<int, int>> targets;

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
          targets.push_back({i, j});
          classroom[i][j] = '.';
          sx = i, sy = j;
        } else if (classroom[i][j] == 'L') {
          xys.push_back({i, j});
          targets.push_back({i, j});
          xyIndex[{i, j}] = maskNum;
          maskNum++;
        } else if (classroom[i][j] == 'R') {
          targets.push_back({i, j});
        }
      }
    }
    if (maskNum == 0) {
      return 0;
    }
    InitPath();
    memset(dp, -1, sizeof(dp));
    // memset(dp1, -1, sizeof(dp1));
    ans = INT_MAX;
    min_queue<tuple<int, int, int, int, int, int>> que;

    auto Add = [&](int sx, int sy, int energy, const int mask, int step) {
      if (dp[sx][sy][energy][mask] != -1 && dp[sx][sy][energy][mask] <= step) {
        return;
      }
      // if (dp1[x][y][mask] != -1 && dp1[x][y][mask] >= energy) {
      //   return;
      // }
      // dp1[x][y][mask] = energy;
      dp[sx][sy][energy][mask] = step;
      int maskNum = __builtin_popcount(mask);
      que.push({maskNum, step, sx, sy, energy, mask});
    };
    Add(sx, sy, energy, (1 << maskNum) - 1, 0);
    while (!que.empty()) {
      const auto [_, step, sx, sy, energy, mask] = que.top();
      que.pop();
      if (step > dp[sx][sy][energy][mask]) {
        continue;
      }
      if (step >= ans) continue;

      for (auto [nx, ny] : targets) {
        int minEnergy = minPath[sx][sy][nx][ny];
        if (minEnergy == -1 || minEnergy > energy) {
          continue;
        }

        int newEnergy = energy - minEnergy;
        int newStep = step + minEnergy;
        int newMask = mask;
        if (classroom[nx][ny] == 'R') {
          newEnergy = E;
        } else if (classroom[nx][ny] == '.') {
          continue;
        } else if (classroom[nx][ny] == 'L') {
          int index = xyIndex[{nx, ny}];
          if (newMask & (1 << index)) {
            newMask ^= (1 << index);
          } else {
            continue;
          }
          if (newMask == 0) {
            ans = min(ans, newStep);
            continue;
          }
        }
        if (newEnergy > 0) {
          Add(nx, ny, newEnergy, newMask, newStep);
        }
      }
    }
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