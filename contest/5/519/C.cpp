
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

// 988 / 999 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  ll shadowPairs(vector<int>& nums) {
    ll ans = 0;
    vector<pair<ll, ll>> sta;
    ll sum = 0;
    for (ll v : nums) {
      while (!sta.empty() && sta.back().first > v) {
        sum -= sta.back().second;
        sta.pop_back();
      }
      if (!sta.empty() && sta.back().first == v) {
        ans += sum - sta.back().second;
        sta.back().second++;
      } else {
        ans += sum;
        sta.push_back({v, 1});
      }
      sum++;
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