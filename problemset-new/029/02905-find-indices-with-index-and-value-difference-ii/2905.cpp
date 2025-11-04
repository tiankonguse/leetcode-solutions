
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

typedef long long ll;
class Solution {
 public:
  vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
    int n = nums.size();
    set<pair<int, int>> h;
    for (int r = indexDifference; r < n; r++) {
      ll v = nums[r];
      const int l = r - indexDifference;
      h.insert({nums[l], l});

      if (abs(v - (*h.begin()).first) >= valueDifference) {
        return {r, (*h.begin()).second};
      }
      if (abs(v - (*h.rbegin()).first) >= valueDifference) {
        return {r, (*h.rbegin()).second};
      }
    }
    return {-1, -1};
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