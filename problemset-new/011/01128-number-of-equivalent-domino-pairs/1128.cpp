
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
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    int ans = 0;
    unordered_map<int, int> count;
    for (const auto& d : dominoes) {
      int a = min(d[0], d[1]);
      int b = max(d[0], d[1]);
      int key = a * 10 + b;
      ans += count[key];
      count[key]++;
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