
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
  int centeredSubarrays(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      unordered_set<int> s;
      int sum = 0;
      for (int j = i; j < n; j++) {
        s.insert(nums[j]);
        sum += nums[j];
        if (s.count(sum)) {
          ans++;
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