
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int minimumRecolors(const string& blocks, int k) {
    int n = blocks.size();
    int ans = n;
    int W = 0, B = 0;
    for (int i = 0; i < n; i++) {
      if (blocks[i] == 'B') {
        B++;
      } else {
        W++;
      }
      if (i < k - 1) {
        continue;
      }
      ans = min(ans, W);
      if (blocks[i - k + 1] == 'B') {
        B--;
      } else {
        W--;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif