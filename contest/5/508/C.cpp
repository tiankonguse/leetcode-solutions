
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

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll NINFL = -INFL;
class Solution {
  ll solve(vector<int>& nums, function<ll(ll)> op) {
    ll f0 = nums[0];
    ll f1 = op(nums[0]);
    ll f2 = NINFL;

    ll ans = max(f0, f1);
    int n = nums.size();

    for (int i=1;i<n;i++) {
      ll a = nums[i];
      ll b = op(a);
      ll nf0 = max(a, f0 + a);
      ll nf1 = max({b, f0 + b, f1 + b});
      ll nf2 = max(f1 + a, f2 + a);

      f0 = nf0;
      f1 = nf1;
      f2 = nf2;
      ans = max({ans, f0, f1, f2});
    }

    return ans;
  }

 public:
  ll maxSubarraySum(vector<int>& nums, int k) {  //
    return max(solve(nums, [&](ll x) { return x * k; }), solve(nums, [&](ll x) { return x / k; }));
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