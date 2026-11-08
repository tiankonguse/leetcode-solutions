
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
  int countSuffix(vector<int>& nums, vector<int>& target) {
    int n = nums.size();
    unordered_map<int, int> mp;
    for (auto v : nums) {
      mp[v]++;
    }
    for (auto v : target) {
      mp[v]--;
      if (mp[v] < 0) {
        return 0;
      }
    }
    if (n == 1) {
      return 1;
    }

    int orderStart = n - 1;
    for (int i = n - 2; i >= 0; i--) {
      if (target[i] < target[i + 1]) {
        break;
      }
      orderStart = i;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (i < orderStart) {
        if (nums[i] != target[i]) return 0;
        continue;
      }
      if (nums[i] == target[i]) {
        ans++;
      } else {
        ans++;
        break;
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