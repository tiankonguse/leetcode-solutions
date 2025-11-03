
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
  vector<int> findMissingElements(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int minVal = nums.front();
    int maxVal = nums.back();
    int count = maxVal - minVal + 1;
    int n = nums.size();
    vector<int> ans;
    ans.reserve(count - n);
    int idx = minVal;
    for (auto num : nums) {
      while (idx < num) {
        ans.push_back(idx);
        idx++;
      }
      idx++;
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