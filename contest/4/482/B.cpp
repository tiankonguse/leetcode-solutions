
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
  ll minimumCost(ll cost1, ll cost2, ll costBoth, ll need1, ll need2) {
    if (cost1 > costBoth) cost1 = costBoth;
    if (cost2 > costBoth) cost2 = costBoth;
    ll ans = 0;
    if (costBoth < cost1 + cost2) {
      int min12 = min(need1, need2);
      ans += min12 * costBoth;
      need1 -= min12;
      need2 -= min12;
    }
    ans += need1 * cost1 + need2 * cost2;
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