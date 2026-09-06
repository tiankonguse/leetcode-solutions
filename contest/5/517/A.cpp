
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
  int countSpecialIntegers(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> leftPos;
    unordered_map<int, int> rightPos;
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
      cnt[nums[i]]++;
      if (leftPos.find(nums[i]) == leftPos.end()) {
        leftPos[nums[i]] = i;
      }
      rightPos[nums[i]] = i;
    }
    int ans = 0;
    for (auto [v, c] : cnt) {
      int l = leftPos[v];
      int r = rightPos[v];
      if (r - l + 1 == c) {
        ans++;
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