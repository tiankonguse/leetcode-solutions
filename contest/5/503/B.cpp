
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
  int passwordStrength(const string& password) {  //
    int ans = 0;
    set<char> s;
    for (char c : password) {
      s.insert(c);
    }
    for (char c : s) {
      if (c >= 'a' && c <= 'z') {
        ans += 1;
      } else if (c >= 'A' && c <= 'Z') {
        ans += 2;
      } else if (c >= '0' && c <= '9') {
        ans += 3;
      } else if (c == '!' || c == '@' || c == '#' || c == '$') {
        ans += 5;
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