
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
  string removeSubstring(const string& s, int k) {
    int n = s.size();
    vector<pair<char, int>> nums;
    nums.reserve(n);
    for (auto c : s) {
      // 更新计数栈
      if (nums.empty() || nums.back().first != c) {
        nums.emplace_back(c, 1);
      } else {
        nums.back().second++;
      }
      // 尝试匹配
      const int sz = nums.size();
      if (sz >= 2) {
        auto [rightC, rightCount] = nums[sz - 1];
        auto [leftC, leftCount] = nums[sz - 2];
        if (rightC == ')' && leftC == '(' && rightCount == k && leftCount >= k) {
          nums.pop_back();
          nums.pop_back();
          if (leftCount > k) {
            nums.emplace_back(leftC, leftCount - k);
          }
        }
      }
    }
    string ans;
    ans.reserve(n);
    for (auto [c, count] : nums) {
      ans.append(count, c);
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