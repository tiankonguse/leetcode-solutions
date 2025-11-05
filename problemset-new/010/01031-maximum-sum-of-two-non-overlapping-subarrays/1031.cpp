
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
  int Solver(vector<int>& nums, int a, int b) {
    int n = nums.size();
    vector<int> prefix(n + 2, 0);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      sum += nums[i - 1];
      if (i < a) {
        continue;
      } else {
        prefix[i] = max(prefix[i - 1], sum);
        sum -= nums[i - a];
      }
    }
    vector<int> suffix(n + 2, 0);
    sum = 0;
    for (int i = n; i >= 1; i--) {
      sum += nums[i - 1];
      if (n - i + 1 < b) {
        continue;
      } else {
        suffix[i] = max(suffix[i + 1], sum);
        sum -= nums[i + b - 2];
      }
    }
    int maxSum = 0;
    for (int i = 1; i <= n; i++) {
      maxSum = max(maxSum, prefix[i] + suffix[i + 1]);
    }
    return maxSum;
  }

 public:
  int maxSumTwoNoOverlap(vector<int>& nums, int a, int b) {  //
    return max(Solver(nums, a, b), Solver(nums, b, a));
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