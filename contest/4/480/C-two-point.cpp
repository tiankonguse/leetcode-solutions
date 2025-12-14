
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
    int l = pos - 1, r = pos + 1;
    while (leftNum > 0) {
      ans += min(leftNum, balance[(l + n) % n]) * ll(pos - l);
      leftNum -= min(leftNum, balance[(l + n) % n]);
      l--;
      
      ans += min(leftNum, balance[r % n]) * ll(r - pos);
      leftNum -= min(leftNum, balance[r % n]);
      r++;
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