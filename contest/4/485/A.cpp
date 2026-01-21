
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
  int vowelConsonantScore(string s) {
    set<char> h = {'a', 'e', 'i', 'o', 'u'};
    int v = 0, c = 0;
    for (auto V : s) {
      if (V >= 'a' && V <= 'z') {
        if (h.count(V)) {
          v++;
        } else {
          c++;
        }
      }
    }
    if (c > 0) {
      return v / c;
    } else {
      return 0;
    }
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