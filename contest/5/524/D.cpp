
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
// 思路：贪心求答案
// 先合并目标区间
// 贪心：目标区间的第一个点，在待选择区间中，选择覆盖这个点且右端点最大的区间。
// 然后更新目标区间的第一个点为这个最大区间的右端点，继续贪心选择。
// 注意事项：第一个点可能不在目标区间，此时需要更新为下一个目标区间的第一个点。
// 无答案情况：如果待选择区间遍历完了，还没找到覆盖目标区间的区间，说明没有答案。
class Solution {
 public:
  int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {
    // 第一步：合并目标区间
    sort(targetIntervals.begin(), targetIntervals.end(), [](vector<int>& a, vector<int>& b) {
      return a[0] < b[0];  //
    });
    vector<pair<int, int>> targets;
    targets.reserve(targetIntervals.size());
    targets.push_back({targetIntervals[0][0], targetIntervals[0][1]});
    for (auto& target : targetIntervals) {
      int l = target[0], r = target[1];
      if (targets.back().second < l) {
        targets.push_back({l, r});
      } else {
        targets.back().second = max(targets.back().second, r);
      }
    }
    for (auto [l, r] : targets) {
      MyPrintf("[%d,%d], ", l, r);
    }
    MyPrintf("\n");

    // 第二步：贪心求答案
    sort(availableIntervals.begin(), availableIntervals.end(), [](vector<int>& a, vector<int>& b) {
      return a[0] < b[0];  //
    });
    int p = targets.front().first;
    int ai = 0;
    int ti = 0;
    int an = availableIntervals.size();
    int tn = targets.size();
    int ans = 0;
    while (ti < tn) {
      // 从 availableIntervals 选择一个区间 [L,R]，使得 L <= p, R >= p，且 R 最大
      int maxR = -1;
      while (ai < an && availableIntervals[ai][0] <= p) {
        maxR = max(maxR, availableIntervals[ai][1]);
        ai++;
      }
      if (maxR == -1) {
        return -1;  // 没有答案
      }
      ans++;
      p = maxR;  // 区间是连续的，所以不能加一
      while (ti < tn && targets[ti].second <= p) {
        ti++;  // 这些区间都可以被覆盖
      }
      if (ti < tn && p < targets[ti].first) {
        p = targets[ti].first;
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