
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
  vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {  //
    sort(occupiedIntervals.begin(), occupiedIntervals.end());
    vector<pair<int, int>> res;
    res.reserve(occupiedIntervals.size());
    int t = occupiedIntervals.front()[0];
    res.push_back({t, t});  // 保证 res 不为空
    for (auto& interval : occupiedIntervals) {
      int start = interval[0];
      int end = interval[1];
      auto& last = res.back();
      if (start <= last.second + 1) {
        last.second = max(last.second, end);
      } else {
        res.emplace_back(start, end);
      }
    }

    vector<vector<int>> ans;
    ans.reserve(res.size());
    for (auto [start, end] : res) {
      if (start < freeStart && freeStart <= end) {
        ans.push_back({start, freeStart - 1}); // 前半段
        start = freeStart;
      }
      if (start <= freeEnd && freeEnd < end) {
        ans.push_back({freeEnd + 1, end}); // 后半段
        end = freeEnd;
      }
      if (start >= freeStart && end <= freeEnd) {
        continue;
      }
      ans.push_back({start, end});
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