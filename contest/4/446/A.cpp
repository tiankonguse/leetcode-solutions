
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
  ll calculateScore(vector<string>& instructions, vector<int>& values) {
    int n = instructions.size();
    vector<int> flag(n, 0);
    ll ans = 0;
    int pos = 0;
    // instructions[i] = "jump" or "add"
    while (pos >= 0 && pos < n && flag[pos] == 0) {
      flag[pos] = 1;
      if (instructions[pos] == "jump") {
        pos += values[pos];
      } else {  // "add"
        ans += values[pos];
        pos++;
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