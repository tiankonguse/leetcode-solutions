
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
  int countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
      m[nums[i]].push_back(i);
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
          int sum = nums[i] + nums[j] + nums[k];
          if (m.count(sum) == 0) continue;
          auto& vec = m[sum];
          auto it = upper_bound(vec.begin(), vec.end(), k);
          ans += vec.end() - it;
        }
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