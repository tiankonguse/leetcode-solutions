
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
  int maximumLengthSubstring(const string& s) {
    int ans = 0;
    int n = s.length();
    vector<int> counts(26, 0);
    int l = 0, r = 0;
    while (r < n) {
      int v = s[r] - 'a';  // 第一步：移动右指针
      r++;
      counts[v]++;
      while (counts[v] > 2) { // 第二步：移动左指针
        counts[s[l] - 'a']--;
        l++;
      }
      ans = max(ans, r - l); // 第三步：更新答案
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif