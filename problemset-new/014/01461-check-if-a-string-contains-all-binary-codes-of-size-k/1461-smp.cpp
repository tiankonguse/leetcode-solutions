
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
  bool hasAllCodes(const string& s, int k) {
    vector<int> vis(1 << k, 0);
    int n = s.size();
    int val = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      val = (val << 1) | (s[i] - '0');
      if (i < k - 1) continue;
      if (vis[val] == 0) {
        vis[val] = 1;
        ans++;
      }
      val &= ~(1 << (k - 1));
    }
    return ans == (1 << k);
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