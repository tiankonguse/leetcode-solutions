
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
  string reverseWords(string s) {
    string vowel = "aeiou";
    set<char> h(vowel.begin(), vowel.end());  // 元音集合
    // 按空格分割单词
    int n = s.size();
    int firstCnt = 0;
    int vowelCnt = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
      if (s[r] == ' ') {
        if (l == 0) {
          firstCnt = vowelCnt;  // 记录第一个单词的元音数量
        } else {
          if (firstCnt == vowelCnt) {
            reverse(s.begin() + l, s.begin() + r);
          }
        }
        l = r + 1;
        vowelCnt = 0;
      } else {
        if (h.count(s[r])) vowelCnt++;
      }
    }
    if (firstCnt == vowelCnt) {
      reverse(s.begin() + l, s.end());
    }
    return s;
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