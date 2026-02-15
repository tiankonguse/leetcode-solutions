
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
  vector<int> toggleLightBulbs(vector<int>& bulbs) {
    sort(bulbs.begin(), bulbs.end());
    vector<int> ans;
    int preV = 0;
    for (auto v : bulbs) {
      if (preV == 0) {
        preV = v;
      } else if (v == preV) {
        preV = 0;
      } else {
        ans.push_back(preV);
        preV = v;
      }
    }
    if (preV != 0) {
      ans.push_back(preV);
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