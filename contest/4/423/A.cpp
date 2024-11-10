
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
  bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> flag(n + 1, 0);
    int l = 0, r = 0;
    while (r < n) {
      l = r;
      while (r + 1 < n && nums[r] < nums[r + 1]) {
        r++;
      }
      for (int i = l; i <= r; i++) {
        flag[i] = r - i + 1;
      }
      r++;
    }
    for(int i=0;i<n;i++){
      int l = i;
      int r = l+k;
      if(r + k - 1 >= n) break;
      if(flag[l] >= k && flag[r] >= k){
         return true;
      }
    }
    return false;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& nums, int k, const int& ans) {
//   TEST_SMP2(Solution, hasIncreasingSubarrays, ans, nums, k);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif