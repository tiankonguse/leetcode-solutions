
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
const ll mod = 1000000007;
class Solution {
 public:
  int minimumCost(vector<int>& nums, const int k) {
    ll sum = 0;
    for (ll v : nums) {
      sum += v;
    }
    if (sum <= k) {
      return 0;
    }
    sum -= k;
    ll num = (sum + k - 1) / k;
    ll A = num;
    ll B = num + 1;
    if (A % 2 == 0) {
      A = A / 2;
    } else {
      B = B / 2;
    }
    A = A % mod;
    B = B % mod;
    return (A * B) % mod;
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