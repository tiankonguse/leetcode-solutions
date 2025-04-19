
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
  int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
    int n = tiles.size();
    sort(tiles.begin(), tiles.end());
    int sum = 0;
    int l = 0, r = 0;
    int ans = 0;
    auto updateRight = [&](auto& v) { sum += v[1] - v[0] + 1; };
    auto updateLeft = [&](auto& v) { sum -= v[1] - v[0] + 1; };
    auto shouldMoveLeft = [&](auto& rv, auto& lv) -> bool { return rv[1] - lv[1] >= carpetLen; };
    while (r < n) {
      auto& rv = tiles[r];
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (shouldMoveLeft(rv, tiles[l])) {  // 第二步：移动左指针
        auto& lv = tiles[l];                  // Change nums[l] to tiles[l]
        l++;
        updateLeft(lv);
      }
      // 第三步：更新答案
      auto& lv = tiles[l];
      if (rv[1] - lv[0] + 1 <= carpetLen) {
        ans = max(ans, sum);
      } else {
        int more = (rv[1] - lv[0] + 1) - carpetLen;
        ans = max(ans, sum - more);
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
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif