
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

int Lis2(vector<pair<int, int>>& nums) {
  sort(nums.begin(), nums.end(), [](auto& a, auto& b) {
    if (a.first == b.first) {
      return a.second > b.second;
    } else {
      return a.first < b.first;
    }
  });
  vector<int> dp;
  for (const auto& v : nums) {
    const int y = v.second;
    auto it = lower_bound(dp.begin(), dp.end(), y);
    if (it == dp.end()) {
      dp.push_back(y);
    } else {
      *it = y;
    }
  }
  return dp.size();
}
class Solution {
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {  //
    vector<pair<int, int>> nums;
    nums.reserve(envelopes.size());
    for (auto& v : envelopes) {
      nums.push_back({v[0], v[1]});
    }
    return Lis2(nums);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>>& envelopes, const int& ans) {
  TEST_SMP1(Solution, maxEnvelopes, ans, envelopes);
}

int main() {
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  Test(envelopes, 3);
  envelopes = {{1, 1}, {1, 1}, {1, 1}};
  Test(envelopes, 1);
  envelopes = {{4, 5}, {4, 6}, {6, 7}, {2, 3}, {1, 1}};
  Test(envelopes, 4);
  return 0;
}

#endif