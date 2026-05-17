
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
  ll minArraySum(vector<int>& nums) {
    int n = nums.size();
    ll ans = 0;
    unordered_map<ll, ll> mp;
    sort(nums.begin(), nums.end());
    for (const ll x : nums) {
      ll sqrtX = sqrt(x);
      ll minVal = x;
      for (ll i = 1; i <= sqrtX; i++) {
        if (x % i == 0) {
          if (mp.count(i)) {
            minVal = min(minVal, i);
          }
          if (mp.count(x / i)) {
            minVal = min(minVal, x / i);
          }
        }
      }
      // for (auto [k, v] : mp) {
      //   MyPrintf("k = %lld, v = %lld\n", k, v);
      // }
      // MyPrintf("x = %lld, minVal = %lld sqrtX = %lld mpSIze=%lld\n", x, minVal, sqrtX, mp.size());
      mp[minVal]++;
      ans += minVal;
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