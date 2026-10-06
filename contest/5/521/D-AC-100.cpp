
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
  vector<ll> vals;
  unordered_map<ll, int> valToIdx;
  void InitDiscretization(const vector<vector<int>>& meetings) {
    vals.reserve(meetings.size() * 2);
    for (auto& m : meetings) {
      vals.push_back(m[0]);
      vals.push_back(m[1]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < vals.size(); i++) {
      valToIdx[vals[i]] = i;
    }
  }

 public:
  ll maxEarnings(vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
    InitDiscretization(meetings);
    int n = valToIdx.size();
    vector<ll> dp(n, 0);  // dp[i] 假设后面还有一个会议，截止到时间 i 前缀的最大收益
    ll ans = 0;
    int p = 0;
    for (auto& m : meetings) {
      int l = valToIdx[m[0]], r = valToIdx[m[1]];
      ll v = m[2];
      while (p < l) {
        if (dp[p] > 0) {
          dp[p + 1] = max(dp[p + 1], dp[p] + vals[p + 1] - vals[p]);
        }
        p++;
      }
      dp[r] = max(dp[r], dp[l] + v);
      ans = max(ans, dp[l] + v);
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