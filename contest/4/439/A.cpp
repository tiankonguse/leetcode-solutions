
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
/*
You are given an integer array nums and an integer k.
An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
Return the largest almost missing integer from nums. If no such integer exists, return -1.
A subarray is a contiguous sequence of elements within an array.
1 <= nums.length <= 50
0 <= nums[i] <= 50
1 <= k <= nums.length
*/
class Solution {
 public:
  int largestInteger(vector<int>& nums, int k) {
    vector<int> count(55, 0);
    for (size_t i = 0; i <= nums.size() - k; ++i) {
      vector<int> seen(55, 0);
      for (size_t j = i; j < i + k; ++j) {
        seen[nums[j]]++;
      }
      for (int num = 0; num < seen.size(); ++num) {
        if (seen[num] > 0) {
          count[num]++;
        }
      }
    }

    int maxMissing = -1;
    for (int num = 0; num < count.size(); ++num) {
      if (count[num] == 1) {
        maxMissing = max(maxMissing, num);
      }
    }
    return maxMissing;
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

#endif