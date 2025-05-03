
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
  vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
    int n = increase.size();
    vector<tuple<int, int, int>> times(n + 1, {0, 0, 0});
    for (int i = 0; i < n; i++) {
      auto [x, y, z] = times[i];
      times[i + 1] = {x + increase[i][0], y + increase[i][1], z + increase[i][2]};
    }

    vector<int> ans(requirements.size(), -1);
    for (int i = 0; i < requirements.size(); i++) {
      tuple<int, int, int> r = {requirements[i][0], requirements[i][1], requirements[i][2]};
      int t = lower_bound(times.begin(), times.end(), r,
                          [](auto& a, auto& b) {
                            auto [a0, a1, a2] = a;
                            auto [b0, b1, b2] = b;
                            return a0 < b0 || a1 < b1 || a2 < b2;
                          }) -
              times.begin();
      if (t == n + 1) {
        continue;
      }

      ans[i] = t;
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