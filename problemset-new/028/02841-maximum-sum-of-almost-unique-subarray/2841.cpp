
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
  ll maxSum(vector<int>& nums, int m, int k) {
    ll ans = 0;
    int n = nums.size();
    unordered_map<int, int> cnt;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      cnt[nums[i]]++;
      sum += nums[i];
      if (i < k - 1) continue;
      if (cnt.size() >= m) {
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