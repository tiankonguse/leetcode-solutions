
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
  int Cal(ll v) {
    int ans = 0;
    while (v) {
      ans += v % 10;
      v /= 10;
    }
    return ans;
  }

 public:
  int maximumSum(vector<int>& nums) {
    unordered_map<int, ll> m;

    ll ans = -1;
    for (ll v : nums) {
      int sum = Cal(v);
      if (m.count(sum) == 0) {
        m[sum] = v;
      } else {
        ans = max(ans, m[sum] + v);
        m[sum] = max(m[sum], v);
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