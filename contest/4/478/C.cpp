
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
  ll Reverse(ll a) {
    ll b = 0;
    while (a) {
      b = b * 10 + a % 10;
      a /= 10;
    }
    return b;
  }

 public:
  int minMirrorPairDistance(vector<int>& nums) {
    int ans = INT_MAX;
    unordered_map<ll, int>  mpR;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      ll v = nums[i];
      ll V = Reverse(v);
      if (mpR.count(v)) {
        ans = min(ans, i - mpR[v]);
      }
      mpR[V] = i;
    }

    if (ans == INT_MAX) {
      ans = -1;
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