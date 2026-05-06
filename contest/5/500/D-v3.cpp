
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

// 第一维升序，第二维降序
int Lis2(vector<pair<int, int>>& pts) {
  sort(pts.begin(), pts.end());

  vector<int> tails;
  for (auto& [x, d] : pts) {
    auto it = lower_bound(tails.begin(), tails.end(), d);
    if (it == tails.end()) {
      tails.push_back(d);
    } else {
      *it = d;
    }
  }
  return tails.size();
}
class Solution {
 public:
  int maxFixedPoints(vector<int>& nums) {
    int n = nums.size();
    vector<pair<int, int>> pts;  // (x = nums[i], d = i - nums[i])
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= i) {
        pts.push_back({i - nums[i], nums[i]});
      }
    }
    return Lis2(pts);
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