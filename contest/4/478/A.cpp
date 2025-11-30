
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int countElements(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end(), greater<int>());
    int ans = 0;
    unordered_map<int, int> se;
    int K = 0;
    for (auto v : nums) {
      if (K - se[v] >= k) {
        ans++;
      }
      se[v]++;
      K++;
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