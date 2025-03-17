
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
  vector<int> getAverages(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n, -1);
    int len = 2 * k + 1;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      sum += nums[i];
      if (i < len - 1) {
        continue;
      }
      ans[i - k] = sum / len;
      sum -= nums[i - len + 1];
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