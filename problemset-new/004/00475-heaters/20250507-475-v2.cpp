
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
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    ll ans = 0;
    for (ll v : houses) {
      auto it = lower_bound(heaters.begin(), heaters.end(), v);
      if (it == heaters.end()) {
        ans = max(ans, v - *prev(it));
      } else if (it == heaters.begin()) {
        ans = max(ans, *it - v);
      } else {
        ans = max(ans, min(*it - v, v - *prev(it)));
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