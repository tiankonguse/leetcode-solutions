
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
const int MaxVal = 100010;
vector<bool> flag(MaxVal, false);
class Solution {
 public:
  vector<int> maximumMEX(vector<int>& nums) {  //
    int n = nums.size();
    vector<int> suffix_mex(n + 1, 0);
    fill(flag.begin(), flag.end(), false);
    for (int i = n - 1; i >= 0; --i) {
      flag[nums[i]] = true;
      int mex = suffix_mex[i + 1];
      while (flag[mex]) {
        mex++;
      }
      suffix_mex[i] = mex;
    }
    vector<int> ans;
    ans.reserve(n);
    fill(flag.begin(), flag.end(), false);
    int R = 0;
    while (R < n) {
      int maxMex = suffix_mex[R];
      ans.push_back(maxMex);
      if (maxMex == 0) {
        R++;
        continue;
      }

      int mex = 0;
      int L = R;
      while (R < n && mex < maxMex) {
        flag[nums[R]] = true;
        R++;
        while (flag[mex]) {
          mex++;
        }
      }
      for (int i = L; i < R; ++i) {
        flag[nums[i]] = false;
      }
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