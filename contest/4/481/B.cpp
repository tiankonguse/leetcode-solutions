
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
  ll minCost(const string& s, vector<int>& cost) {
    int n = s.size();
    vector<ll> stat(26, 0);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      stat[s[i] - 'a'] += cost[i];
      sum += cost[i];
    }
    ll ans = sum;
    for (int i = 0; i < 26; i++) {
      ans = min(ans, sum - stat[i]);
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