
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
      if (nums.empty() || nums.back().first != c) {
        nums.emplace_back(c, 1);
      } else {
        nums.back().second++;
      }
      int sz = nums.size();
      if (sz >= 2 && nums.back().first == ')' && nums.back().second == k && nums[sz - 2].second >= k) {
        nums.pop_back();
        nums[sz - 2].second -= k;
        if (nums[sz - 2].second == 0) {
          nums.pop_back();
        }
      }
    }
    string ans;
    ans.reserve(n);
    for (auto& p : nums) {
      ans.append(p.second, p.first);
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