
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
  long long minMoves(vector<int>& balance) {
    int n = balance.size();
    ll sum = 0;
    ll pos = -1;
    for (int i = 0; i < n; i++) {
      int v = balance[i];
      sum += v;
      if (v < 0) {
        pos = i;
      }
    }
    if (sum < 0) {
      return -1;
    }
    if (pos == -1) {
      return 0;
    }
    ll ans = 0;
    int leftNum = -balance[pos];
    for (int r = 1; leftNum > 0; r++) {
      int L = (pos - r + n) % n;
      int R = (pos + r) % n;
      ans += min(leftNum, balance[L]) * ll(r);
      leftNum -= min(leftNum, balance[L]);

      ans += min(leftNum, balance[R]) * ll(r);
      leftNum -= min(leftNum, balance[R]);
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