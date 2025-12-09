
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
  vector<int> sortByReflection(vector<int>& nums) {
    vector<pair<ll, ll>> nums2;
    nums2.reserve(nums.size());
    // 二进制翻转
    for (const ll v : nums) {
      ll v2 = 0;
      ll V = v;
      while (V) {
        v2 = (v2 << 1) | (V & 1);
        V >>= 1;
      }
      nums2.emplace_back(v2, v);
    }
    sort(nums2.begin(), nums2.end());
    vector<int> ans;
    for (auto& [_, v] : nums2) {
      ans.push_back(v);
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