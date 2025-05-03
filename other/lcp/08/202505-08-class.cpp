
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

struct Cmp {
  const int index;
  Cmp(int index) : index(index) {}
  bool operator()(const tuple<int, int, int>& a, const tuple<int, int, int>& b) const {
    if (index == 0) {
      return get<0>(a) < get<0>(b);
    } else if (index == 1) {
      return get<1>(a) < get<1>(b);
    } else if (index == 2) {
      return get<2>(a) < get<2>(b);
    }
    return false;
  }
};

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
      int t0 = lower_bound(times.begin(), times.end(), r, Cmp(0)) - times.begin();
      if (t0 == n + 1) {
        continue;
      }

      int t1 = lower_bound(times.begin() + t0, times.end(), r, Cmp(1)) - times.begin();
      if (t1 == n + 1) {
        continue;
      }
      int t2 = lower_bound(times.begin() + t1, times.end(), r, Cmp(2)) - times.begin();
      if (t2 == n + 1) {
        continue;
      }
      ans[i] = t2;
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