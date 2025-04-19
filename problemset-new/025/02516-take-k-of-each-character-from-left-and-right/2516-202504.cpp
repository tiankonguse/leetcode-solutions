
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
  int takeCharacters(const string& s, int k) {
    int n = s.size();
    vector<int> nums(3, 0);
    for (int i = 0; i < n; i++) {
      nums[s[i] - 'a']++;
    }
    for (auto v : nums) {
      if (v < k) return -1;
    }
    int l = 0, r = 0;
    int ans = 0;
    auto updateRight = [&](int v) { nums[v]--; };
    auto updateLeft = [&](int v) { nums[v]++; };
    auto shouldMoveLeft = [&](int rv) -> bool { return nums[rv] < k; };
    while (r < n) {
      int rv = s[r] - 'a';
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (l < r && shouldMoveLeft(rv)) {  // 第二步：移动左指针
        int lv = s[l] - 'a';
        l++;
        updateLeft(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
    }
    return n - ans;
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