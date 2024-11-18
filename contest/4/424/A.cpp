
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
  int countValidSelections(vector<int>& nums) {
    int n = nums.size();
    vector<int> pre(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1] + nums[i - 1];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      if (v != 0) continue;
      int left = pre[i - 1];
      int right = pre[n] - pre[i];
      if (left + 1 == right) {
        ans += 1;
      } else if (left == right + 1) {
        ans += 1;
      } else if (left == right) {
        ans += 2;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  TEST_SMP1(Solution, countValidSelections, ans, jump);
}

int main() {
  Test({1, 0, 2, 0, 3}, 2);
  Test({2, 3, 4, 0, 4, 1, 0}, 0);
  return 0;
}

#endif