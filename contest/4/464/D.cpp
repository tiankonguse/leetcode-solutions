
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
enum { DIR_LEFT = 0, DIR_RIGHT = 1 };
class Solution {
 public:
  int maxWalls(const vector<int>& robots_, const vector<int>& distance, vector<int>& walls) {
    int rn = robots_.size();
    int wn = walls.size();
    vector<tuple<int, int, int>> robots(rn);  // [pos, leftDis, rightDis]
    for (int i = 0; i < rn; i++) {
      robots[i] = {robots_[i], distance[i], distance[i]};
    }
    sort(robots.begin(), robots.end());
    sort(walls.begin(), walls.end());
    // 第一步：修复机器人的射程
    for (int i = 0; i < rn; i++) {  // 射程不能打到下一个机器人
      auto& [pos, leftDis, rightDis] = robots[i];
      if (i > 0) {
        leftDis = min(leftDis, pos - get<0>(robots[i - 1]) - 1);
      }
      if (i + 1 < rn) {
        rightDis = min(rightDis, get<0>(robots[i + 1]) - pos - 1);
      }
    }
    auto ShotRange = [&walls](int l, int r) -> int {  // 区间内墙的数量
      if (l > r) return 0;
      return upper_bound(walls.begin(), walls.end(), r) - lower_bound(walls.begin(), walls.end(), l);
    };
    // 第二步：动态规划求最优答案
    vector<vector<int>> dp(rn + 1, vector<int>(2, 0));  // dp[i][j] 下个机器人向 j 方向射击时，前 i 个机器人的最优解
    // 第 0 个机器人射程设置为0
    for (int i = 1; i <= rn; i++) {
      auto& [pos, leftDis, rightDis] = robots[i - 1];
      int nowRightAns = dp[i - 1][DIR_RIGHT] + ShotRange(pos, pos + rightDis);
      int nowLeftAns = dp[i - 1][DIR_LEFT] + ShotRange(pos - leftDis, pos);
      dp[i][DIR_RIGHT] = max(nowRightAns, nowLeftAns);
      int nowRightAns2 = dp[i - 1][DIR_RIGHT] + ShotRange(pos, pos + rightDis);  // 有交叉情况
      if (i < rn) {
        auto& [pos2, leftDis2, rightDis2] = robots[i];
        nowRightAns2 -= ShotRange(pos2 - leftDis2, pos + rightDis);
      }
      dp[i][DIR_LEFT] = max(nowRightAns2, nowLeftAns);
    }
    return max(dp[rn][DIR_LEFT], dp[rn][DIR_RIGHT]);
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