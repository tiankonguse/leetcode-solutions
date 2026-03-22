
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
  bool uniformArray(vector<int>& nums1) {
    int n = nums1.size();
    ll minMaxVal[2] = {INT_MAX, INT_MAX};
    int cnt[2] = {0, 0};
    for (ll v : nums1) {
      minMaxVal[v % 2] = min(minMaxVal[v % 2], v);
      cnt[v % 2]++;
    }
    if (cnt[0] == 0 || cnt[1] == 0) {
      return true;
    }
    if (minMaxVal[1] < minMaxVal[0]) {
      return true;
    }

    return false;
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