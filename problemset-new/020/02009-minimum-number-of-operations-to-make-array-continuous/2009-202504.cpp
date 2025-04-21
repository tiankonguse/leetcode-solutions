
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
  int minOperations(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int l = 0, r = 0;
    int ans = n;
    unordered_map<int, int> cnt;
    auto updateAdd = [&](auto& v) { cnt[v]++; };
    auto updateDel = [&](auto& v) {
      cnt[v]--;
      if (cnt[v] == 0) {
        cnt.erase(v);
      }
    };
    auto shouldMove = [&](auto& lv, auto& rv) -> bool { return rv - lv >= n; };
    while (r < n) {
      auto& rv = nums[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (shouldMove(nums[l], rv)) {  // 第二步：移动左指针
        auto& lv = nums[l];
        l++;
        updateDel(lv);
      }

      ans = min(ans, n - int(cnt.size()));  // 第三步：更新答案
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