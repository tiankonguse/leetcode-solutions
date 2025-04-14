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
  int minimumPairRemoval(vector<int>& nums) {
    int ans = 0;
    auto isNonDecreasing = [&]() {
      for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < nums[i - 1]) {
          return false;
        }
      }
      return true;
    };
    while (!isNonDecreasing()) {
      int n = nums.size();
      int minSum = INT_MAX;
      int minIndex = -1;
      for (int i = 0; i < n - 1; i++) {
        if (nums[i] + nums[i + 1] < minSum) {
          minSum = nums[i] + nums[i + 1];
          minIndex = i;
        }
      }
      nums[minIndex] = nums[minIndex] + nums[minIndex + 1];
      nums.erase(nums.begin() + minIndex + 1);
      ans++;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif