
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
  string smallestPalindrome(const string& s) {
    vector<int> stat(26, 0);
    for (char c : s) {
      stat[c - 'a']++;
    }
    char oddVal = 'a';
    for (int i = 0; i < 26; i++) {
      if (stat[i] % 2 == 1) {
        oddVal = i + 'a';
        stat[i]--;
        break;
      }
    }
    int n = s.size();
    string ans(n, oddVal);
    int left = 0, right = n - 1;
    for (int i = 0; i < 26; i++) {
      if (stat[i] > 0) {
        char c = i + 'a';
        int count = stat[i] / 2;
        while (count--) {
          ans[left++] = c;
          ans[right--] = c;
        }
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
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif