
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

typedef long long ll;
class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    const int n = intervals.size();
    // printf("n=%d\n", n);
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
      if (a[0] != b[0]) return a[0] < b[0];
      return a[1] > b[1];
    });

    vector<pair<int, int>> nums;
    for (auto& v : intervals) {
      int l = v[0], r = v[1];
      while (nums.size() && nums.back().second >= r) {
        nums.pop_back();
      }
      nums.push_back({l, r});
    }

    int ans = 0;
    map<int, int> m;  // right boundary answer
    int preMax = 0;
    int preR = nums.front().first - 1;
    for (auto [l, r] : nums) {
      // printf("preMax=%d preR=%d\n", preMax, preR);
      auto it = m.upper_bound(preR);  // next ans
      while (it != m.end() && it->first <= l) {
        preMax = max(preMax, it->second);
        preR = it->first;
        it = m.upper_bound(preR);  // next ans
      }
      // printf("preMax=%d preR=%d\n", preMax, preR);
      m[r] = preMax + 1;
      // printf("l=%d r=%d m[r]=%d\n", l, r, m[r]);
      ans = max(ans, m[r]);
    }

    return n - ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif