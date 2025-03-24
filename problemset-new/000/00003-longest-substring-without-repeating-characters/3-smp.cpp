
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
 public:
  int lengthOfLongestSubstring(const string& s) {
    int n = s.size();
    int ans = 0;
    unordered_map<char, int> h;
    for (int i = 0, j = 0; i < n; ++i) {
      h[s[i]]++;
      while (h[s[i]] > 1) {
        h[s[j++]]--;
      }
      ans = max(ans, i - j + 1);
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