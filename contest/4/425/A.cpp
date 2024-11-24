
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
  int minimumSumSubarray(vector<int>& nums, int l, int r) {
    int n = nums.size();
    vector<int> sums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      sums[i] = sums[i - 1] + nums[i - 1];
    }
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
      for (int j = i + l - 1; j <= n && j <= i + r - 1; j++) {
        int tmp = sums[j] - sums[i - 1];
        if (tmp > 0) {
          ans = min(ans, tmp);
        }
      }
    }
    if (ans == INT_MAX) {
      ans = -1;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, int l, int r, const int& ans) {
  TEST_SMP3(Solution, minimumSumSubarray, ans, nums, l, r);
}

int main() {
  Test({3, -2, 1, 4}, 2, 3, 1);
  Test({-2, 2, -3, 1}, 2, 3, -1);
  Test({1, 2, 3, 4}, 2, 4, 3);
  return 0;
}

#endif