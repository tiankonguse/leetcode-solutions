
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
  vector<vector<int>> pairSums(vector<int>& nums, int target) {
    vector<vector<int>> ans;
    unordered_map<ll, int> m;
    for (auto v : nums) {
      if (m[target - v] > 0) {
        ans.push_back({target - v, v});
        m[target - v]--;
      } else {
        m[v]++;
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