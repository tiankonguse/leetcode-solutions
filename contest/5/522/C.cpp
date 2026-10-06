
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
enum { EVEN = 0, ODD = 1 };
ll flag[2] = {1, -1};
class Solution {
  vector<vector<ll>> memoLeft;
  vector<vector<ll>> memoRight;
  vector<int> nums;
  int n;
  void Init(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    memoLeft.resize(2, vector<ll>(n, INT64_MIN / 2));
    memoRight.resize(2, vector<ll>(n, INT64_MIN / 2));
  }
  ll DfsLeft(int i, int o) {
    ll& ret = memoLeft[o][i];
    if (ret != INT64_MIN / 2) return ret;
    ret = INT64_MIN / 4;
    if (o == EVEN) {
      ret = max(ret, nums[i] * flag[o]);
    }
    if (i > 0) {
      ret = max(ret, nums[i] * flag[o] + DfsLeft(i - 1, 1 - o));
    }
    return ret;
  }
  ll DfsRight(int i, int o) {
    ll& ret = memoRight[o][i];
    if (ret != INT64_MIN / 2) return ret;
    ret = nums[i] * flag[o];
    if (i + 1 < n) {
      ret = max(ret, nums[i] * flag[o] + DfsRight(i + 1, 1 - o));
    }
    return ret;
  }

 public:
  ll maxAlternatingSum(vector<int>& nums_) {
    Init(nums_);
    ll ans = INT64_MIN;
    for (int i = 0; i < n; i++) {
      ans = max(ans, DfsLeft(i, EVEN));
      ans = max(ans, DfsLeft(i, ODD));
      if (i > 0) {
        ans = max(ans, DfsRight(i, EVEN));
      }
    }
    for (int i = 1; i + 1 < n; i++) {
      for (int li = 0; li < 2; li++) {
        ll left = DfsLeft(i - 1, li);
        ll right = DfsRight(i + 1, 1 - li);
        ans = max(ans, left + right);
      }
    }

    return ans;
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