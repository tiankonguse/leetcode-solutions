
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int minSwaps(vector<int>& nums) {
    int n = nums.size();
    int k = accumulate(nums.begin(), nums.end(), 0);
    int ans = n + 1;
    int sum = 0;
    for (int i = 0; i < n + k; i++) {
      sum += nums[i % n];
      if (i < k - 1) {
        continue;
      }
      ans = min(ans, k - sum);
      sum -= nums[(i - k + 1 + n) % n];
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif