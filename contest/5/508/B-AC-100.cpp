
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
    sort(occupiedIntervals.begin(), occupiedIntervals.end(), [](const vector<int>& a, const vector<int>& b) {        //
      return a[0] < b[0];
    });
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
      // start 在 [freeStart, freeEnd] 左边，分三种情况
      if (start < freeStart && end < freeStart) {
        ans.push_back({start, end});
        continue;
      }
      if (start < freeStart && end <= freeEnd) {
        ans.push_back({start, freeStart - 1});
        continue;
      }
      if (start < freeStart && freeEnd < end) {
        ans.push_back({start, freeStart - 1});
        ans.push_back({freeEnd + 1, end});
        continue;
      }
      // start 在 [freeStart, freeEnd] 右边
      if (start > freeEnd) {
        ans.push_back({start, end});
        continue;
      }

      // start 在 [freeStart, freeEnd] 区间内
      if (freeStart <= start && end <= freeEnd) {
        continue;
      }
      if (start <= freeEnd && freeEnd < end) {
        ans.push_back({freeEnd + 1, end});
        continue;
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