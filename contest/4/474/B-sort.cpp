
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
  long long maxProduct(vector<int>& nums) {
    const ll maxVal = 1e5;
    sort(nums.begin(), nums.end(), [](int a, int b) { return abs(a) > abs(b); });
    ll a = abs(nums[0]);
    ll b = abs(nums[1]);
    return a * b * maxVal;
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