
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
  int equalSubstring(const string& s, const string& t, int maxCost) {
    int n = s.size();
    int l = 0, r = 0;
    int ans = 0;
    int cost = 0;
    auto updateRight = [&](int v) { cost += v; };
    auto updateLeft = [&](int v) { cost -= v; };
    auto shouldMoveLeft = [&]() -> bool { return cost > maxCost; };

    while (r < n) {
      int rv = abs(int(s[r]) - int(t[r]));
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (shouldMoveLeft()) {              // 第二步：移动左指针
        int lv = abs(int(s[l]) - int(t[l]));  // Corrected to calculate the left value
        l++;
        updateLeft(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
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