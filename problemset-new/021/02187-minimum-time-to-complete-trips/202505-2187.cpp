
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
  long long minimumTime(vector<int>& time, ll totalTrips) {
    ll l = 0, r = totalTrips * time.front();  // [l, r) 000111
    auto Check = [&](ll mid) {
      ll sum = 0;
      for (auto t : time) {
        sum += mid / t;
      }
      return sum >= totalTrips;
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