
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
  int maxDistance(const string& moves) {  //
    int n = moves.size();
    set<char> s = {'U', 'D', 'L', 'R'};
    int ans = 0;
    for (char c : s) {
      int x = 0, y = 0;
      for (char o : moves) {
        if (o == '_') {
          o = c;
        }
        x += (o == 'U' ? 1 : o == 'D' ? -1 : 0);
        y += (o == 'R' ? 1 : o == 'L' ? -1 : 0);
      }
      ans = max(ans, abs(x) + abs(y));
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