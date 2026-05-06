
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
 public:
  vector<int> countOppositeParity(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    int cnt[2] = {0, 0};
    for (int i = n - 1; i >= 0; i--) {
      int v = nums[i] % 2;
      ans[i] = cnt[1 - v];
      cnt[v]++;
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