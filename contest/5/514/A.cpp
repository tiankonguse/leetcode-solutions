
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
  double minPrice(vector<int>& prices, vector<int>& discounts) {  //
    sort(prices.rbegin(), prices.rend());
    sort(discounts.rbegin(), discounts.rend());
    double ans = 0;
    int nd = discounts.size();
    int di = 0;
    for (auto p : prices) {
      if (di < nd && discounts[di] > 0) {
        ans += p * (100.0 - discounts[di]) / 100.0;
        di++;
      } else {
        ans += p;
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