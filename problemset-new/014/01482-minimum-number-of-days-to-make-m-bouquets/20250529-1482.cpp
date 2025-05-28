
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
  int minDays(vector<int>& bloomDay, ll m, ll k) {
    ll n = bloomDay.size();
    if (n < m * k) {
      return -1;
    }
    ll l = 0, r = 1e10;  // [l, r) 000111
    auto Check = [&](ll mid) -> bool {
      ll sum = 0;
      ll cnt = 0;
      int pre = 0;
      for (auto t : bloomDay) {
        if (t <= mid) {
          pre = pre + 1;
          if (pre == k) {
            sum = sum + 1;
            pre = 0;
          }
        } else {
          pre = 0;
        }
      }
      return sum >= m;
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