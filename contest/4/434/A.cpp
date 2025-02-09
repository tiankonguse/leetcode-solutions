
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
  int countPartitions(vector<int>& nums) {
    int ans = 0;
    int sum = 0;
    for (auto v : nums) {
      sum += v;
    }
    int n = nums.size();
    int pre = 0;
    for (int i = 0; i + 1 < n; i++) {
      int v = nums[i];
      pre += v;
      sum -= v;
      int diff = pre - sum;
      if (diff % 2 == 0) {
        ans++;
      }
    }
    return ans;
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