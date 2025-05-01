
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
  int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
    // buildings[i] = [x, y]
    unordered_map<int, vector<int>> hx, hy;
    int ans = 0;
    for (auto& building : buildings) {
      int x = building[0], y = building[1];
      hx[x].push_back(y);
      hy[y].push_back(x);
    }
    for (auto& [x, ys] : hx) {
      sort(ys.begin(), ys.end());
    }
    for (auto& [y, xs] : hy) {
      sort(xs.begin(), xs.end());
    }
    for (auto& building : buildings) {
      int x = building[0], y = building[1];
      auto& hxy = hx[x];
      auto& hyx = hy[y];
      if (y != hxy.front() && y != hxy.back() && x != hyx.front() && x != hyx.back()) {
        ans++;
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