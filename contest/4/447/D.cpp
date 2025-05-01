
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
  vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    vector<int> datas = nums;
    sort(datas.begin(), datas.end());
    datas.erase(unique(datas.begin(), datas.end()), datas.end());
    int m = datas.size();
    unordered_map<int, int> h;
    for (int i = 0; i < m; i++) {
      h[datas[i]] = i;
    }

    vector<vector<int>> dp(m, vector<int>(20, 0));
    for (int i = 0; i < m; i++) {
      dp[i][0] = lower_bound(datas.begin(), datas.end(), datas[i] - maxDiff) - datas.begin();
      for (int j = 1; j < 20; j++) {
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
      }
    }

    vector<int> result;
    result.reserve(queries.size());
    for (auto& q : queries) {
      // queries[i] = [ui, vi]
      if (nums[q[0]] == nums[q[1]]) {  // 本身就是答案
        result.push_back(0);
        continue;
      }
      int l = h[nums[q[0]]], r = h[nums[q[1]]];
      if (l > r) {
        swap(l, r);
      }
      if (dp[r][19] > l) {  // 不联通，没答案
        result.push_back(-1);
        continue;
      }
      if (l == r) {
        result.push_back(1);
        continue;
      }
      int ans = 0;
      for (int j = 19; l < r && j >= 0; j--) {
        if (dp[r][j] > l) {
          ans += (1 << j);
          r = dp[r][j];
        }
      }
      if (r > l) {
        ans++;
      }

      result.push_back(ans);
    }

    return result;
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