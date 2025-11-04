
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
  ll interchangeableRectangles(vector<vector<int>>& nums) {
    ll ans = 0;
    map<pair<int, int>, ll> cnts;
    for (auto& v : nums) {
      int g = gcd(v[0], v[1]);
      pair<int, int> key = {v[0] / g, v[1] / g};
      ans += cnts[key];
      cnts[key]++;
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