
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
  ll minimumTime(vector<int>& d, vector<int>& r) {
    const ll d1 = d[0], d2 = d[1];
    const ll r1 = r[0], r2 = r[1];
    const ll lcm = r1 / __gcd(r1, r2) * r2;
    auto OK = [&](ll mid) -> bool {
      ll x12 = mid / lcm;
      ll x1 = mid / r1 - x12;
      ll x2 = mid / r2 - x12;
      ll x0 = mid - x1 - x2 - x12;
      ll leftR1 = max(d1 - x2, 0ll);
      ll leftR2 = max(d2 - x1, 0ll);
      return x0 >= leftR1 + leftR2;
    };
    ll L = 0, R = 1e18;
    while (L < R) {
      ll mid = L + (R - L) / 2;  // [1, mid]
      if (OK(mid)) {
        R = mid;
      } else {
        L = mid + 1;
      }
    }
    return L;
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