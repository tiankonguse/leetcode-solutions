
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
    ll l = 0, r = 1e9 + 1;  // [l, r) 000111
    auto Check = [&](ll mid) -> bool {
      int p1 = 0;
      ll L = heaters[p1] - mid;
      ll R = heaters[p1] + mid;
      for (ll house : houses) {
        while (p1 < heaters.size() && house > R) {
          p1++;
          if (p1 == heaters.size()) {
            return false;
          }

          L = heaters[p1] - mid;
          R = heaters[p1] + mid;
        }
        if (house < L || house > R) {
          return false;
        }
      }
      return true;
    };
    while (l < r) {
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
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