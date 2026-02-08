
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
  vector<ll> mergeAdjacent(vector<int>& nums) {
    vector<ll> ans;
    ans.reserve(nums.size());
    for (ll v : nums) {
      while (ans.size() > 0 && ans.back() == v) {
        ans.pop_back();
        v *= 2;
      }
      ans.push_back(v);
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