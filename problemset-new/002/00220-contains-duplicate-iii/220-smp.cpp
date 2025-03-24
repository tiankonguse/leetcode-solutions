
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
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
    int n = nums.size();
    map<ll, int> h;
    for (int i = 0; i < n; i++) {
      ll v = nums[i];
      ll l = v - valueDiff;
      ll r = v + valueDiff;
      auto it = h.lower_bound(l);
      if (it != h.end() && it->first <= r) {
        return true;
      }
      h[v]++;
      if (i < indexDiff) continue;
      h[nums[i - indexDiff]]--;
      if (h[nums[i - indexDiff]] == 0) {
        h.erase(nums[i - indexDiff]);
      }
    }
    return false;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif