
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
  int minPenalty(int period, vector<int>& lights, vector<int>& arrivalTime) {
    ll ans = 0;
    ll maxLight = 0;
    for (int i = 0; i < lights.size(); i++) {
      maxLight = max(maxLight, (ll)lights[i]);
    }
    for (ll car : arrivalTime) {
      car %= period;
      if (car >= maxLight) {
        ans = max(ans, period - car);
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