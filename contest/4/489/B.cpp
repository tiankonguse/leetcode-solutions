
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
  int firstUniqueFreq(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (auto& num : nums) {
      mp[num]++;
    }
    unordered_map<int, int> mp2;
    for (auto& p : mp) {
      mp2[p.second]++;
    }
    for (auto v : nums) {
      int cnt = mp[v];
      if (mp2[cnt] == 1) {
        return v;
      }
    }
    return -1;
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