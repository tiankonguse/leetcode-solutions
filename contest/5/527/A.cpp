
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
  vector<vector<string>> findMismatchedSegments(string s1, string s2) {
    vector<vector<string>> ans;
    int n = s1.size();
    string tmp1;
    string tmp2;
    for (int i = 0; i < n; i++) {
      if (s1[i] != s2[i]) {
        tmp1.push_back(s1[i]);
        tmp2.push_back(s2[i]);
      } else {
        if (!tmp1.empty()) {
          ans.push_back({tmp1, tmp2});
          tmp1.clear();
          tmp2.clear();
        }
      }
    }
    if (!tmp1.empty()) {
      ans.push_back({tmp1, tmp2});
      tmp1.clear();
      tmp2.clear();
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