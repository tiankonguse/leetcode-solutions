
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
  int maxFixedPoints(vector<int>& nums) {
    int n = nums.size();
    vector<pair<int, int>> pts;  // (x = nums[i], d = i - nums[i])
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= i) {
        pts.push_back({nums[i], i - nums[i]});
      }
    }
    // x 升序；x 相同则 d 降序
    sort(pts.begin(), pts.end(), [](const auto& a, const auto& b) {
      if (a.first != b.first) return a.first < b.first;
      return a.second > b.second;
    });

    // 在 d 上求最长非递减子序列
    vector<int> tails;
    for (auto& [x, d] : pts) {
      auto it = upper_bound(tails.begin(), tails.end(), d);
      if (it == tails.end())
        tails.push_back(d);
      else
        *it = d;
    }

    return tails.size();
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