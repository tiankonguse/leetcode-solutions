
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
  vector<int> decimalRepresentation(int n) {
    vector<int> ans;
    ll base = 1;
    while (n) {
      if (n % 10 == 1) {
        ans.push_back(base * (n % 10));
      }
      n /= 10;
      base *= 10;
    }
    std::reverse(ans.begin(), ans.end());
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