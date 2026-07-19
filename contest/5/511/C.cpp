
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
  int n;

  pair<int, int> Count(const string& s) {
    int counts[2] = {0, 0};
    for (char c : s) {
      if (c == '0') {
        counts[0]++;
      } else if (c == '1') {
        counts[1]++;
      }
    }
    return {counts[0], counts[1]};
  }
  bool Check(const string& s, const string& str) {
    auto [s0, s1] = Count(s);
    auto [str0, str1] = Count(str);
    if (str0 > s0 || str1 > s1) {
      return false;
    }
    int need0 = s0 - str0;
    int i = 0, j = 0;
    while (i < n && j < n) {
      while (i < n && s[i] == '1') i++;
      while (j < n && (str[j] == '1' || (str[j] == '?' && need0 == 0))) j++;
      if (i == n || j == n) break;
      if (str[j] == '?') need0--;
      if (i < j) return false;
      i++, j++;
    }
    return true;
  }

 public:
  vector<bool> transformStr(const string& s, vector<string>& strs) {  //
    vector<bool> ans;
    ans.reserve(strs.size());
    n = s.size();
    for (const auto& str : strs) {
      ans.push_back(Check(s, str));
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