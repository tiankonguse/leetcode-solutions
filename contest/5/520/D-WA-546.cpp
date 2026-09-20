
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
  vector<int> largestPower(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < 15; i++) {
      stable_sort(nums.begin(), nums.end(), [&](int a, int b) {
        a = a & (1 << i);
        b = b & (1 << i);
        return a > b;
      });
    }
    vector<int> ans(15);
    for (int i = 0; i < 15; i++) {
      int j = 14 - i;
      for (auto v : nums) {
        v = v & (1 << j);
        if (v == 0) break;
        ans[i]++;
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