
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
  long long minNumberOfSeconds(ll mountainHeight, vector<int>& workerTimes) {
    // w * (1+ x) * x /2 = t, x = (t*2/w + 1/4)^0.5 - 1/2
    ll l = 1, r = (1 + mountainHeight) * mountainHeight / 2 * workerTimes.front();  // [l, r) 000111
    auto Check = [&](ll t) -> bool {
      ll sum = 0;
      for (auto w : workerTimes) {
        sum += sqrt(t * 2.0 / w + 1.0 / 4) - 1.0 / 2;
      }
      return sum >= mountainHeight;
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