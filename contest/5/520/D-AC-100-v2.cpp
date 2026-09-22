
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
  int Count(const int b, vector<int>& nums) {        //
    sort(nums.begin(), nums.end(), greater<int>());  //
    int cnt = 0;
    int offset = 0;
    while (offset < nums.size()) {
      int v = nums[offset] & (1 << b);
      if (v == 0) break;
      offset++;
    }
    cnt = offset;
    while (offset < nums.size()) {
      nums[offset] &= ~(1 << b);
      offset++;
    }

    return cnt;
  }

 public:
  vector<int> largestPower(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(15);
    for (int i = 0; i < 15; i++) {
      const int b = 14 - i;
      ans[i] = Count(b, nums);
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