
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
  int longestSemiRepetitiveSubstring(const string& s) {
    int n = s.size();
    int l = 0, r = 0;
    int ans = 0;
    int cnt = 0;
    auto updateRight = [&](auto v) {
      if (r > 0 && s[r] == s[r - 1]) cnt++;
    };
    auto updateLeft = [&](auto v) {
      if (s[l] == s[l + 1]) cnt--;
    };
    auto shouldMoveLeft = [&](int rv) -> bool { return cnt > 1; };
    while (r < n) {
      auto rv = s[r];
      updateRight(rv);  // 第一步：移动右指针
      r++;

      while (shouldMoveLeft(rv)) {  // 第二步：移动左指针
        auto lv = s[l];
        updateLeft(lv);
        l++;
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