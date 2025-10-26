
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
  long long countStableSubarrays(vector<int>& capacity) {
    ll n = capacity.size();
    ll sum = 0;
    ll ans = 0;
    map<pair<ll, ll>, int> mp;
    for (int i = 0; i < n; i++) {
      const ll v = capacity[i];
      sum += v;
      const pair<ll, ll> p = {sum - 2 * v, v};
      if (i >= 2 && mp.count(p)) {
        ans += mp[p];
      }
      if (i > 0) {
        mp[{sum - v, capacity[i - 1]}]++;
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