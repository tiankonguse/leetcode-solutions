
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
  int Common(const string& s1, const string& s2) {
    int len = 0;
    for (int j = 0; j < s1.size() && j < s2.size(); j++) {
      if (s1[j] == s2[j]) {
        len++;
      } else {
        break;
      }
    }
    return len;
  }

 public:
  vector<int> longestCommonPrefix(vector<string>& words) {
    int n = words.size();
    vector<int> ans(n, 0);
    if (n <= 2) {
      return ans;
    }
    vector<int> commonLen(n + 2, 0);
    for (int i = 1; i < n; i++) {
      auto& s1 = words[i];
      auto& s2 = words[i - 1];
      commonLen[i] = Common(s1, s2);
    }
    vector<int> leftMax(n + 2, 0);
    for (int i = 1; i < n - 1; i++) {
      leftMax[i] = max(leftMax[i - 1], commonLen[i]);
    }
    vector<int> rightMax(n + 2, 0);
    for (int i = n - 1; i >= 0; i--) {
      rightMax[i] = max(rightMax[i + 1], commonLen[i + 1]);
    }

    ans[0] = rightMax[1];
    ans[n - 1] = leftMax[n - 2];
    for (int i = 1; i + 1 < n; i++) {
      ans[i] = max(leftMax[i - 1], rightMax[i + 1]);
      auto& s1 = words[i + 1];
      auto& s2 = words[i - 1];
      ans[i] = max(ans[i], Common(s1, s2));
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