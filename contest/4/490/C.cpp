
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
  string maximumXor(string s, string t) {
    int cnt[2] = {0, 0};
    for (auto c : t) {
      cnt[c - '0']++;
    }
    for (auto& c : s) {
      const char v = (c - '0') ^ 1;
      if (cnt[v] > 0) {
        cnt[v]--;
        c = '1';
      } else {
        cnt[1 - v]--;
        c = '0';
      }
    }
    return s;
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