
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
  int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
    int n = nums.size();
    int m = changeIndices.size();
    vector<int> flag(n, 0);
    int index = 0;
    ll l = 1, r = m + 1;  // [l, r) 000111
    auto Check = [&](ll mid) -> bool {
      index++;  // 标记为 index
      ll sum = 0;
      int flagNum = 0;
      for (int i = mid - 1; i >= 0; i--) {
        int v = changeIndices[i] - 1;
        if (flag[v] != index) {
          flagNum++;
          flag[v] = index;  // 这一秒进行标记
          sum += nums[v];   // 前面需要减少的次数
        } else {
          if (sum > 0) {
            sum--;
          }
        }
      }
      return flagNum == n && sum <= 0;
    };
    while (l < r) {
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (l == m + 1) {
      return -1;
    }
    return l;
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