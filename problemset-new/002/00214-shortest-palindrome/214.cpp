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

// s 原始字符串; ss 预处理后的字符串;  p 各中心的半径
void Manacher(const string& s, string& ss, vector<int>& p) {
  int n = s.size();
  int nn = n * 2 + 2;
  ss.resize(nn);
  p.resize(nn);

  ss[0] = '$';
  ss[nn - 1] = '#';
  for (int i = 0; i < n; i++) {
    ss[i * 2 + 1] = '#';
    ss[i * 2 + 2] = s[i];
  }
  int r = 0, id = 0;  // 到达最远 r 时，中心为 id, (id-r, id+r)
  for (int i = 1; i < nn; i++) {
    p[i] = 1;
    if (r > i) {
      p[i] = min(p[2 * id - i], r - i);
    }
    while (i + p[i] < nn && i - p[i] > 0 && ss[i + p[i]] == ss[i - p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      r = i + p[i];
      id = i;
    }
  }
}

class Solution {
 public:
  const string shortestPalindrome(const string& s) {
    string ss;
    vector<int> p;
    Manacher(s, ss, p);
    int nn = ss.size();
    int minLen = nn - 1;  // 忽略第一个字符 $
    for (int i = 1; i < nn; i++) {
      if (i != p[i]) continue;
      int len = nn - (i + p[i]);
      if (len < minLen) {
        minLen = len;
      }
    }
    // MyPrintf("ss=%s\n", ss.data());
    // for (int i = 1; i < nn; i++) {
    //   MyPrintf(" %d", p[i]);
    // }
    // MyPrintf("\n");
    // MyPrintf("minLen=%d\n", minLen);

    string ans;
    ans.reserve(nn);
    for (int i = nn - 1; i >= nn - minLen; i--) {
      if (ss[i] == '#') continue;
      ans.push_back(ss[i]);
    }
    ans.append(s);
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE
void Test(const string& s, const string& ans) {
  TEST_SMP1(Solution, shortestPalindrome, ans, s);
}

int main() {
  Test("ababbbabbaba", "ababbabbbababbbabbaba");
  // Test("aacecaaa", "aaacecaaa");
  // Test("abcd", "dcbabcd");
  // Test("b", "b");
  // Test("ba", "aba");
  // Test("baa", "aabaa");
  // Test("baaa", "aaabaaa");
  // Test("abaaa", "aaabaaa");
  // Test("aabaaa", "aaabaaa");
  // Test("aaabaaa", "aaabaaa");
  return 0;
}
#endif
