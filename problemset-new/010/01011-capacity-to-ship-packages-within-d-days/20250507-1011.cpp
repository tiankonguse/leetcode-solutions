
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
  int shipWithinDays(vector<int>& weights, int days) {
    ll l = *max_element(weights.begin(), weights.end());
    ll r = accumulate(weights.begin(), weights.end(), 0ll);  // [l, r) 000111
    auto Check = [&](ll mid) -> bool {
      ll day = 1;
      ll sum = 0;
      for (ll v : weights) {
        if (sum + v > mid) {
          day++;
          sum = 0;
        }
        sum += v;
      }
      return day <= days;
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