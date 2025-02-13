
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

int dir4[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
class Solution {
 public:
  int maxDistance(const string& s, int k) {
    int n = s.size();
    const string dirs = "NESW";
    map<char, int> h;
    for (int i = 0; i < 4; i++) {
      h[dirs[i]] = i;
    }

    int ans = 0;

    int x = 0, y = 0;
    vector<int> cmds(4, 0);
    int cmdAll = 0;

    for (auto d : s) {
      int D = h[d];
      cmds[D]++;
      cmdAll++;

      x += dir4[D][0];
      y += dir4[D][1];

      int leftCmd = cmdAll;
      if (x >= 0 && y >= 0) {  // 0 & 1
        leftCmd -= cmds[0] + cmds[1];
      } else if (x >= 0 && y <= 0) {  // 1 & 2
        leftCmd -= cmds[1] + cmds[2];
      } else if (x <= 0 && y <= 0) {  // 2 & 3
        leftCmd -= cmds[2] + cmds[3];
      } else {  // 3 & 0
        leftCmd -= cmds[3] + cmds[0];
      }
      leftCmd = min(leftCmd, k);
      ans = max(ans, abs(x) + abs(y) + leftCmd * 2);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif