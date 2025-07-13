
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
  string processStr(string s) {
    string ans;
    for (auto c : s) {
      if ('a' <= c && c <= 'z') {
        ans.push_back(c);
      } else if (c == '*') {
        if (!ans.empty()) ans.pop_back();
      } else if (c == '#') {
        ans += ans;
      } else if (c == '%') {
        reverse(ans.begin(), ans.end());
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