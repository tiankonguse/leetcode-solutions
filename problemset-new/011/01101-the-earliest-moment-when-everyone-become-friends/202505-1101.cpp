
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
    ll r = accumulate(weights.begin(), weights.end(), 0);
    auto Check = [&](ll mid) -> bool {
      int day = 1;
      ll sum = 0;
      for (auto w : weights) {
        if (sum + w > mid) {
          day++;
          sum = w;
          if (day > days) {
            return false;
          }
        } else {
          sum += w;
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