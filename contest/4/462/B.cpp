
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
  int sortPermutation(vector<int>& nums) {
    int ans = -1;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] != i) {
        if (ans == -1) {
          ans = i;
        } else {
          ans = ans & i;
        }
      }
    }
    if (ans == -1) ans = 0;
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