
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
  int longestArithmetic(const vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    int tmpDiff = INT_MAX;
    int tmpCnt = 0;
    for (int i = 1; i < n; i++) {  // 第一步：不修改
      int diffVal = nums[i] - nums[i - 1];
      if (diffVal == tmpDiff) {
        tmpCnt++;
      } else {
        tmpDiff = diffVal;
        tmpCnt = 2;
      }
      ans = max(ans, tmpCnt);
      MyPrintf("i=%d diff=%d cnt=%d ans=%d\n", i, diffVal, tmpCnt, ans);
    }
    if (ans < n) {
      ans = ans + 1;  // 第二步：修改端点
      MyPrintf("fix ans=%d\n", ans);
    }
    if (ans == n) {
      return ans;
    }
    // 第三步：修改中间
    vector<int> preCnt(n + 2, 1), preDiffVal(n + 2, INT_MAX);
    for (int i = 2; i <= n; i++) {
      preDiffVal[i] = nums[i - 1] - nums[i - 2];
      if (preDiffVal[i] == preDiffVal[i - 1]) {
        preCnt[i] = preCnt[i - 1] + 1;
      } else {
        preCnt[i] = 2;
      }
    }
    for (int i = 1; i <= n; i++) {
      MyPrintf("pre[%d] = <diff=%d,cnt=%d>\n", i, preDiffVal[i], preCnt[i]);
    }
    vector<int> sufCnt(n + 2, 1), sufDiffVal(n + 2, INT_MAX);
    for (int i = n - 1; i >= 1; i--) {
      sufDiffVal[i] = nums[i] - nums[i - 1];
      if (sufDiffVal[i] == sufDiffVal[i + 1]) {
        sufCnt[i] = sufCnt[i + 1] + 1;
      } else {
        sufCnt[i] = 2;
      }
    }
    for (int i = 1; i <= n; i++) {
      MyPrintf("suf[%d] = <diff=%d,cnt=%d>\n", i, sufDiffVal[i], sufCnt[i]);
    }
    for (int i = 2; i < n; i++) {  // 枚举修改 i
      int leftVal = nums[i - 1 - 1];
      int rightVal = nums[i + 1 - 1];
      MyPrintf("i=%d len=%d \n", i, rightVal + leftVal);
      if ((rightVal + leftVal) % 2 != 0) {
        MyPrintf("i=%d  skip\n", i);
        continue;
      }
      int avgVal = (rightVal + leftVal) / 2;
      int diffVal = avgVal - leftVal;
      if (diffVal == preDiffVal[i - 1]) {
        MyPrintf("try left i=%d ans=%d\n", i, preCnt[i - 1] + 2);
        ans = max(ans, preCnt[i - 1] + 2);
      }
      if (diffVal == sufDiffVal[i + 1]) {
        MyPrintf("try right i=%d ans=%d\n", i, sufCnt[i + 1] + 2);
        ans = max(ans, sufCnt[i + 1] + 2);
      }
      if (diffVal == preDiffVal[i - 1] && diffVal == sufDiffVal[i + 1]) {
        MyPrintf("try both i=%d ans=%d\n", i, preCnt[i - 1] + sufCnt[i + 1] + 1);
        ans = max(ans, preCnt[i - 1] + sufCnt[i + 1] + 1);
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