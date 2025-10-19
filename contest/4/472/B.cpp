
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
  int longestBalanced(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    unordered_map<int, int> count0;
    unordered_map<int, int> count1;
    for (int i = 0; i < n; ++i) {
      count0.clear();
      count1.clear();
      for (int j = i; j < n; ++j) {
        if (nums[j] % 2 == 0) {
          count0[nums[j]]++;
        } else {
          count1[nums[j]]++;
        }
        if (count0.size() == count1.size()) {
          ans = max(ans, j - i + 1);
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