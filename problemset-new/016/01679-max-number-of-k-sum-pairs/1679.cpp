
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
  int maxOperations(vector<int>& nums, int k) {
    long long sum = k;
    unordered_map<long long, int> m;
    int ans = 0;
    for (auto v : nums) {
      long long o = sum - v;
      if (m[o] > 0) {
        ans++;
        m[o]--;
      } else {
        m[v]++;
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