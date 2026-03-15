
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
  long long countCommas(long long n) {
    ll ans = 0;
    ll L = 1000;
    ll cnt = 1;
    while (L <= n) {
      ll R = L * 1000;  // [L, R)
      if (n < R) {
        ans += (n - L + 1) * cnt;
        break;
      } else {
        ans += (R - L) * cnt;
        cnt++;
        L = R;
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