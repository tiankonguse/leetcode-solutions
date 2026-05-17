
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
  int countKthRoots(int l, int r, int k) {
    ll yL = ceil(pow(l, 1.0 / k));
    while (powl(yL, k) < l) yL++;

    ll yR = floor(pow(r, 1.0 / k));
    while (powl(yR + 1 , k) <= r) yR++;

    return yR - yL;
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