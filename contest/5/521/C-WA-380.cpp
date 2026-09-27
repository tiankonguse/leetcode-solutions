
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
  int maxSubarray(vector<int>& nums) {
    unordered_map<ll, vector<int>> valPos;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int v = nums[i];
      valPos[v].push_back(i);
    }
    int ans = 0;
    vector<int> preMax(n);  // [i, preMax[i])
    for (int i = 0; i < n; i++) {
      preMax[i] = n;
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int v = nums[i] + nums[j];
        auto itV = valPos.find(v);
        if (itV == valPos.end()) {
          continue;
        }
        auto& pos = itV->second;
        auto itI = lower_bound(pos.begin(), pos.end(), i);  // [i,j]
        if (itI != pos.end()) {
          int idx = max(*itI, j);
          preMax[i] = min(preMax[i], idx);
        }
        if (itI != pos.begin()) {
          --itI;
          int idx = max(*itI, j);
          preMax[i] = min(preMax[i], idx);
        }
      }
    }
    int pre = n;
    for (int i = n - 1; i >= 0; i--) {
      pre = min(pre, preMax[i]);
      ans = max(ans, pre - i);
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