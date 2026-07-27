
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
  int largestInteger(int n, int s) {  //
    if (n * 9 < s) return -1;
    if (s == 0) return 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (s >= 9) {
        ans = ans * 10 + 9;
        s -= 9;
      } else {
        ans = ans * 10 + s;
        s = 0;
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