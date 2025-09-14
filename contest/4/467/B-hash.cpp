
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
  vector<int> maxKDistinct(vector<int>& nums, int k) {
    unordered_set<int> s;
    sort(nums.begin(), nums.end(), greater<int>());
    for (const auto& n : nums) {
      s.insert(n);
      if (s.size() == k) break;
    }
    vector<int> result(s.begin(), s.end());
    sort(result.begin(), result.end(), greater<int>());
    return result;
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