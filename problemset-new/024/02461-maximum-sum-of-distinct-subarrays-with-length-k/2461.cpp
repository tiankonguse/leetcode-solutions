
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
  ll maximumSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    ll ans = 0;
    ll sum = 0;
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
      sum += nums[i];
      cnt[nums[i]]++;
      if (i < k - 1) {
        continue;
      }
      if (cnt.size() == k) {
        ans = max(ans, sum);
      }
      sum -= nums[i - k + 1];
      cnt[nums[i - k + 1]]--;
      if (cnt[nums[i - k + 1]] == 0) {
        cnt.erase(nums[i - k + 1]);
      }
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