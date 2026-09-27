
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
    vector<pair<int, int>> indexNums;
    indexNums.reserve(nums.size());
    map<int, int> mp;
    for (int v : nums) {
      mp[v]++;
      indexNums.push_back({mp[v], v});
    }
    sort(indexNums.begin(), indexNums.end());
    vector<int> ans;
    ans.reserve(nums.size());
    for (auto [_, v] : indexNums) {
      ans.push_back(v);
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