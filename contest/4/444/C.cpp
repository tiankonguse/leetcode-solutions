
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
  map<tuple<int, int, int, int>, pair<int, int>> dp;

 public:
  int maxProduct(vector<int>& nums, const int k, const int limit) {
    int hasZero = 0;
    for (auto v : nums) {
      if (v == 0) {
        hasZero = 1;
        break;
      }
    }
    // 判断选择 0 是否有答案
    auto dfs0 = [&](auto& dfs, const int flag, const int N, const int sum, const int L) -> pair<int, int> {
      if (N == 0) {  // 递归出口， flag 必须是奇数，和 K 必须是 0
        if (flag == 1 && sum == 0) {
          return {0, 0};
        } else {
          return {-1, 0};
        }
      }

      const tuple<int, int, int, int> t = make_tuple(flag, N, sum, L);
      if (dp.count(t)) {
        return dp[t];
      }

      const int v = nums[N - 1];
      int sign = flag ? -1 : 1;  // 偶数加，奇数减

      pair<int, int> ans = dfs(dfs, flag, N - 1, sum, L);  // 不选择 v
      MyPrintf("dfs0: flag %d N %d sum %d L %d v %d noSelect ans {%d, %d}\n", flag, N, sum, L, v, ans.first,
               ans.second);

      pair<int, int> tmp = dfs(dfs, flag ^ 1, N - 1, sum - v * sign, L);  // 选择 v
      if (tmp.first != -1) {
        ans = max(ans, {tmp.first, tmp.second + (v == 0 ? 1 : 0)});
        MyPrintf("dfs0: flag %d N %d sum %d L %d v %d select ans {%d, %d}\n", flag, N, sum, L, v, tmp.first,
                 tmp.second + (v == 0 ? 1 : 0));
      }

      MyPrintf("dfs0: flag %d N %d sum %d L %d v %d ans {%d, %d}\n", flag, N, sum, L, v, ans.first, ans.second);
      return dp[t] = ans;
    };
    auto CheckZeroAns = [&]() -> bool {
      dp.clear();
      pair<int, int> ans = {-1, 0};                      // (乘积，0的个数)
      ans = max(ans, dfs0(dfs0, 1, nums.size(), k, 0));  // 最后一个数是奇数
      ans = max(ans, dfs0(dfs0, 0, nums.size(), k, 0));  // 最后一个数是偶数
      return ans.first != -1 && ans.second > 0;
    };
    int hasZeroAns = 0;
    if (hasZero && CheckZeroAns()) {
      hasZeroAns = 1;
    }
    MyPrintf("hasZero %d hasZeroAns %d\n", hasZero, hasZeroAns);

    // 删除 nums 中的所有 0
    nums.erase(remove(nums.begin(), nums.end(), 0), nums.end());

    MyPrintf("nums[%d]: ", (int)nums.size());
    for (auto v : nums) {
      MyPrintf("%d ", v);
    }
    MyPrintf("\n");
    int n = nums.size();

    dp.clear();
    auto dfs = [&](auto& dfs, const int flag, const int N, const int sum, const int L) -> pair<int, int> {
      if (N == 0) {  // 递归出口， flag 必须是奇数，和 K 必须是 0
        if (flag == 1 && sum == 0) {
          return {1, 0};
        } else {
          return {-1, 0};
        }
      }

      const tuple<int, int, int, int> t = make_tuple(flag, N, sum, L);
      if (dp.count(t)) {
        return dp[t];
      }

      const int v = nums[N - 1];
      int sign = flag ? -1 : 1;  // 偶数加，奇数减

      pair<int, int> ans = dfs(dfs, flag, N - 1, sum, L);  // 不选择 v
      MyPrintf("flag %d N %d sum %d L %d v %d noSelect ans {%d, %d}\n", flag, N, sum, L, v, ans.first, ans.second);
      if (v <= L) {  // 选择 v
        pair<int, int> tmp = dfs(dfs, flag ^ 1, N - 1, sum - v * sign, L / v);
        if (tmp.first != -1) {
          ans = max(ans, {tmp.first * v, tmp.second + 1});
          MyPrintf("flag %d N %d sum %d L %d v %d select ans {%d, %d}\n", flag, N, sum, L, v, tmp.first * v,
                   tmp.second + 1);
        }
      }
      MyPrintf("flag %d N %d sum %d L %d v %d ans {%d, %d}\n", flag, N, sum, L, v, ans.first, ans.second);
      return dp[t] = ans;
    };

    pair<int, int> ans = {-1, 0};              // (乘积，个数)
    ans = max(ans, dfs(dfs, 1, n, k, limit));  // 最后一个数是奇数
    ans = max(ans, dfs(dfs, 0, n, k, limit));  // 最后一个数是偶数
    if (ans.first == -1 || ans.second == 0) {
      if (hasZeroAns) {
        return 0;
      } else {
        return -1;
      }
    } else {
      return ans.first;
    }
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