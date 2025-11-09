
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
  int minimumDistance(vector<int>& nums) {
    int n = nums.size();
    vector<int> preLastIndex(n + 2, -1);
    unordered_map<int, int> lastIndex;
    for (int i = 1; i <= n; i++) {
      int num = nums[i - 1];
      if (lastIndex.count(num)) {
        preLastIndex[i] = lastIndex[num];
      }
      lastIndex[num] = i;
    }
    vector<int> suffFistIndex(n + 2, -1);
    lastIndex.clear();
    for (int i = n; i >= 1; i--) {
      int num = nums[i - 1];
      if (lastIndex.count(num)) {
        suffFistIndex[i] = lastIndex[num];
      }
      lastIndex[num] = i;
    }
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
      if (preLastIndex[i] != -1 && suffFistIndex[i] != -1) {
        ans = min(ans, (suffFistIndex[i] - preLastIndex[i]) * 2);
      }
    }
    if (ans == INT_MAX) {
      return -1;
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