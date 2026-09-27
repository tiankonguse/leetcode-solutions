
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

class Solution {
 public:
  vector<int> rearrangeArray(vector<int>& nums) {
    map<int, int> mp;
    for (int v : nums) {
      mp[v]++;
    }
    vector<int> ans;
    ans.reserve(nums.size());
    while (!mp.empty()) {
      for (auto it = mp.begin(); it != mp.end();) {
        ans.push_back(it->first);
        if (--it->second == 0) {
          it = mp.erase(it);
        } else {
          ++it;
        }
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