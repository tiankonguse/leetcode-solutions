
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

int grids[8][8][2];
const int dir[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

class Solution {
 public:
  bool canReach(vector<int>& start, vector<int>& target) {  //
    memset(grids, 0, sizeof(grids));
    int sx = start[0], sy = start[1];
    int tx = target[0], ty = target[1];
    if (sx == tx && sy == ty) return true;
    grids[sx][sy][0] = 1;
    queue<tuple<int, int, int>> q;
    q.push({sx, sy, 0});
    while (!q.empty()) {
      auto [x, y, step] = q.front();
      q.pop();

      if (x == tx && y == ty) return step % 2 == 0;
      for (int i = 0; i < 8; i++) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        int nstep = (step + 1) % 2;
        if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) continue;
        if (grids[nx][ny][nstep] != 0) continue;
        grids[nx][ny][nstep] = 1;
        q.push({nx, ny, nstep});
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