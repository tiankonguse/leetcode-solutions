
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

typedef long long ll;
class Solution {
 public:
  int similarPairs(vector<string>& words) {
    unordered_map<int, int> m;
    int ans = 0;
    for (auto& w : words) {
      int bit = 0;
      for (auto v : w) {
        bit = bit | (1 << (v - 'a'));
      }
      ans += m[bit];
      m[bit]++;
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