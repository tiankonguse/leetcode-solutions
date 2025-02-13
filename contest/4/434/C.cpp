
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


a1 a2 a3 a4 ... an
b1 b2 b3 b4 ... bn

a[j] + nums[i,j]

=k: 前面都不变
=x: 前面都加1


*/
class Solution {
 public:
  int maxFrequency(vector<int>& nums, const int k) {
    int n = nums.size();
    int ans = 0;
    vector<int> stats(51, 0);
    for (auto v : nums) {
      stats[v]++;
    }

    vector<int> suffixSum(n + 2, 0);
    for (int i = n; i >= 1; i--) {
      int v = nums[i - 1];
      suffixSum[i] = suffixSum[i + 1];
      if (v == k) {
        suffixSum[i]++;
      }
    }

    ans = stats[k];
    for (int i = 1; i <= 50; i++) {
      if (i == k || stats[i] == 0) continue;
      int preMax = 0;
      int kNum = 0;
      for (int j = 1; j <= n; j++) {
        int v = nums[j - 1];
        if (v == k) {
          kNum++;
        } else if (v == i) {
          if (j > 1) {
            preMax++;
          }
          preMax = max(preMax, kNum + 1);
        } 

        int tmpAns = preMax + suffixSum[j + 1];
        ans = max(ans, tmpAns);
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