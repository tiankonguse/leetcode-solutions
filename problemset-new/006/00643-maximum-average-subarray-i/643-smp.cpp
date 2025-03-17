
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
  double findMaxAverage(vector<int>& nums, int k) {
    ll sum = 0, maxSum = INT_MIN;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      sum += nums[i];
      if (i < k - 1) {
        continue;
      }
      maxSum = max(maxSum, sum);
      sum -= nums[i - k + 1];
    }

    return maxSum * 1.0 / k;
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