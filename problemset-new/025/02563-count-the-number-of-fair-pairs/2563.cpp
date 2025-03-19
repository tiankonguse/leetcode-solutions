
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
  vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
    const int N = 50;
    const int N2 = 2 * N + 1;
    int n = nums.size();
    vector<int> ans;
    ans.reserve(n - k + 1);
    vector<int> count(N2, 0);
    for (int i = 0; i < n; i++) {
      count[nums[i] + N]++;
      if (i < k - 1) {
        continue;
      }
      int sum = 0;
      for (int j = 0; j < N2; j++) {
        sum += count[j];
        if (sum >= x) {
          ans.push_back(min(j - N, 0));
          break;
        }
      }
      count[nums[i - k + 1] + N]--;
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