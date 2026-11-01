
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
  ll Merge(ll a, const ll B) {
    ll ans = a;
    ll b = B;
    while (b) {
      ans = ans * 10;
      b /= 10;
    }
    return ans + B;
  }

 public:
  int minMergedInteger(vector<int>& nums) {
    int n = nums.size();
    ll ans = INT64_MAX;
    for (int i = 0; i < n; i += 2) {
      ans = min(ans, Merge(nums[i], nums[i + 1]));
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