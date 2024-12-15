
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
const int N = 30;
class Solution {
  vector<int> dp;
  vector<int> nums;

  int Dfs(int i, int h) {
    if (i >= 26) return 0;
    int& ret = dp[i];
    if (ret != -1) return ret;
    const int v = nums[i];
    ret = INT_MAX;

    if (v == 0 || v == h) {  // 已经满足
      return ret = Dfs(i + 1, h);
    }

    // 独自处理, 多了删除，少了添加
    int minNow = min(abs(h - v), v);
    ret = min(ret, minNow + Dfs(i + 1, h));

    // 与下一个一起处理
    if (i + 1 < 26 && nums[i + 1] < h) {
      int minNow = v;
      if (v > h) {
        minNow = min(minNow, v - h);
      }
      ret = min(ret, max(minNow, h - nums[i + 1]) + Dfs(i + 2, h));
    }
    return ret;
  }

 public:
  int makeStringGood(const string& s) {
    int H = 0;
    nums.resize(N, 0);
    for (auto v : s) {
      nums[v - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
      // printf("v=%d num=%d\n", i, nums[i]);
      H = max(H, nums[i]);
    }

    int ans = INT_MAX;
    for (int h = 0; h <= H; h++) {  //
      dp.clear();
      dp.resize(28, -1);
      ans = min(ans, Dfs(0, h));
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

#endif©leetcode