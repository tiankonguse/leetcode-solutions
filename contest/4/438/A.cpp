
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  bool hasSameDigits(string s) {
    vector<int> nums;
    nums.reserve(s.size());
    for (auto c : s) {
      nums.push_back(c - '0');
    }
    int n = nums.size();
    for (int i = n - 1; i > 1; i--) {
      for (int j = 0; j < i; j++) {
        nums[j] = (nums[j] + nums[j + 1]) % 10;
        // printf("%d ", nums[j]);
      }
      // printf("\n");
    }
    return nums[0] == nums[1];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif©leetcode