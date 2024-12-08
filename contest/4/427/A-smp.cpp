
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
  vector<int> constructTransformedArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      ans[i] = nums[((i + nums[i]) % n + n) % n];
    }
    return ans;
  }
};
#ifdef USACO_LOCAL_JUDGE

void Test(vector<int> nums, vector<int> ans) {
  TEST_SMP1(Solution, constructTransformedArray, ans, nums);
}

int main() {
  Test({3, -2, 1, 1}, {1, 1, 1, 3});
  Test({-1, 4, -1}, {-1, -1, 4});
  return 0;
}

#endif

/*
 */