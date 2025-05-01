
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
  vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
    sort(nums.begin(), nums.end());
    vector<int> preSum(nums.size() + 1, 0);
    for (int i = 0; i < nums.size(); i++) {
      preSum[i + 1] = preSum[i] + nums[i];
    }
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto q : queries) {
      int p = upper_bound(preSum.begin(), preSum.end(), q) - preSum.begin();
      ans.push_back(p - 1);
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