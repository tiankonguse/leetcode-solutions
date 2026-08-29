
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
  string toZeroOne(int c) {
    // 返回 8 位二进制字符串
    string ret;
    for (int i = 0; i < 8; i++) {
      ret += (c & (1 << i)) ? '1' : '0';
    }
    return ret;
  }
  bool CheckPalindromic(const string& s) {
    int n = s.size();
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
      if (s[i] != s[j]) return false;
    }
    return true;
  }

 public:
  bool isPalindromic(string s) {
    int n = s.size();
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
      if (i == j) {
        string t = toZeroOne(s[i]);
        if (!CheckPalindromic(t)) return false;
      } else {
        string a = toZeroOne(s[i]);
        string b = toZeroOne(s[j]);
        std::reverse(b.begin(), b.end());
        if (a != b) return false;
      }
    }
    return true;
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