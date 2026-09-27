
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
  int maxEqualAdjacentPairs(vector<int>& nums) {
    unordered_map<ll, int> mp;
    int n = nums.size();
    int ans = 0;
    int maxCount = 0;
    for (int i = 0; i < n - 1; ++i) {
      ll a = nums[i], b = nums[i + 1];
      a--, b--;
      if (a > b) swap(a, b);
      if (a == b) {
        ans++;
      } else {
        ll key = a * 1000000000 + b;
        mp[key]++;
        maxCount = max(maxCount, mp[key]);
      }
    }
    return ans + maxCount;
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