
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
    unordered_map<ll, ll> cnts;
    cnts.reserve(nums.size());
    const ll base = 1e6;
    for (auto& v : nums) {
      int g = gcd(v[0], v[1]);
      ll a = v[0] / g;
      ll b = v[1] / g;
      ll key = a * base + b;
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