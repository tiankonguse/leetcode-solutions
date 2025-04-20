
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
  int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    // fruits[i] = [positioni, amounti]
    int l = 0, r = 0;
    int n = fruits.size();
    ll ans = 0;
    ll sum = 0;
    auto updateRight = [&](auto& v) {
      int position = v[0];
      int amount = v[1];
      if (position + k < startPos || startPos + k < position) {
        return;
      }
      sum += amount;
    };
    auto updateLeft = [&](auto& v) {
      int position = v[0];
      int amount = v[1];
      if (position + k < startPos || startPos + k < position) {
        return;
      }
      sum -= amount;
    };
    auto shouldMoveLeft = [&](auto& lv, auto& rv) -> bool {
      int lpos = lv[0];
      int rpos = rv[0];
      if (rpos <= startPos) {  // lpos <= rpos <= startPos
        if (lpos + k < startPos) {
          return true;
        } else {
          return false;
        }
      } else if (lpos >= startPos) {  // startPos <= lpos <= rpos
        return false;                 // 射线，不需要移动左端点了
      } else {                        // lpos <= startPos <= rpos
        if ((startPos - lpos) * 2 + (rpos - startPos) > k && (rpos - startPos) * 2 + (startPos - lpos) > k) {
          return true;
        } else {
          return false;
        }
      }
    };
    while (r < n) {
      auto& rv = fruits[r];
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (l < r && shouldMoveLeft(fruits[l], rv)) {  // 第二步：移动左指针
        auto& lv = fruits[l];
        l++;
        updateLeft(lv);
      }

      ans = max(ans, sum);  // 第三步：更新答案
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