
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
const ll mod = 1e9 + 7;
class Solution {
 public:
  ll countTrapezoids(vector<vector<int>>& points) {
    ll ans = 0;
    unordered_map<int, ll> H;
    for (auto& p : points) {
      H[p[1]]++;
    }
    ll pre = 0;
    for (auto [_, cnt] : H) {
      ll now = cnt * (cnt - 1) / 2 % mod;
      ans = (ans + pre * now) % mod;
      pre = (pre + now) % mod;
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