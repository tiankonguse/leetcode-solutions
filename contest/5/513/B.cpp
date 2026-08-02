
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
  int countRatioSubarrays(vector<int>& nums, int a, int b) {
    int n = nums.size();
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int x = 0;  // 偶数的个数
      int y = 0;  // 奇数的个数
      for (int j = i; j < n; j++) {
        if (nums[j] % 2 == 0) {
          x++;
        } else {
          y++;
        }
        if (y > 0 && x * b <= y * a) {
          ans++;
        }
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