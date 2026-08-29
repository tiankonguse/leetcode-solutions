
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
  bool CheckPalindromic(const string& s) {
    int n = s.size();
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
      if (s[i] != s[j]) return false;
    }
    return true;
  }

 public:
  bool isPalindromic(string s) {
    string ret;
    ret.reserve(s.size() * 8);
    for (int c : s) {
      for (int i = 0; i < 8; i++) {
        ret += (c & (1 << i)) ? '1' : '0';
      }
    }
    return CheckPalindromic(ret);
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