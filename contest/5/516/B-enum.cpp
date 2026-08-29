
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
  vector<vector<int>> findDisappearedNumbers(vector<int>& nums, int lower, int upper) {
    int n = nums.size();
    unordered_set<int> s(nums.begin(), nums.end());
    vector<vector<int>> ret;
    ret.reserve(nums.size() + 1);

    int i = 0;
    for (; lower <= upper; lower++) {
      if (s.count(lower)) {
        continue;
      }
      if (!ret.empty() && ret.back().back() == lower - 1) {
        ret.back().back() = lower;
      } else {
        ret.push_back({lower, lower});
      }
    }
    return ret;
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