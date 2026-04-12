
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
  int longestBalanced(string s) {
    int ans = 0;
    ans = max(ans, longestBalancedEx(s));
    reverse(s.begin(), s.end());
    ans = max(ans, longestBalancedEx(s));
    return ans;
  }
  int longestBalancedEx(const string& s) {
    int n = s.size();
    int ans = 0;
    // 复杂度需要是 O(n log(n))
    int rightCnt[2] = {0, 0};
    for (auto c : s) {
      rightCnt[c - '0']++;
    }

    unordered_map<int, int> preDiff;
    preDiff[0] = -1;
    int cnt[2] = {0, 0};
    for (int i = 0; i < n; i++) {
      const int v = s[i] - '0';
      cnt[v]++;
      rightCnt[v]--;
      int diff = cnt[1] - cnt[0];
      // 情况1：不替换的答案
      if (preDiff.count(diff)) {
        ans = max(ans, i - preDiff[diff]);
      }
      // 后缀选择 0 来与前缀交换
      if (rightCnt[0] > 0) {
        if (preDiff.count(diff - 2)) {
          ans = max(ans, i - preDiff[diff - 2]);
        }
      }
      // 后缀选择 1 来与前缀交换
      if (rightCnt[1] > 0) {
        if (preDiff.count(diff + 2)) {
          ans = max(ans, i - preDiff[diff + 2]);
        }
      }
      if (!preDiff.count(diff)) {
        preDiff[diff] = i;
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