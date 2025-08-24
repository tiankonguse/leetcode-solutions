
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
  vector<int> maxValue(vector<int>& nums) {
    int n = nums.size();
    vector<pair<int, int>> sta;  // [maxVal, leftIndex]
    for (int i = 0; i < n; i++) {
      int v = nums[i];
      pair<int, int> p = {v, i};
      while (!sta.empty() && sta.back().first > v) {
        p.first = max(p.first, sta.back().first);  // 进行合并
        p.second = sta.back().second;              // 坐标是递减的，所以记录最左边的坐标即可
        sta.pop_back();
      }
      sta.push_back(p);
    }
    // 全部合并完了，开始计算答案
    vector<int> ans(n, 0);
    int R = n;  // 右边界
    for (int i = sta.size() - 1; i >= 0; i--) {
      auto [maxVal, L] = sta[i];
      for(int j=L; j<R;j++){
        ans[j] = maxVal;
      }
      R = L;
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