
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
  string s;
  vector<vector<int>> dp;
  int Check(char a, char b) {  //
    // 连续， a 与 b 也连续
    if (a > b) {
      swap(a, b);
    }
    return b - a == 1 || (b == 'z' && a == 'a');
  }
  int Solver(int i, int j) {
    if (j < i) return 1;   // 空串
    if (dp[i][j] != -1) {  // 记忆化
      return dp[i][j];
    }
    int len = j - i + 1;
    if (len % 2 == 1) {
      return dp[i][j] = 0;  // 奇数不可能被消除
    }
    if (len == 2) {
      return dp[i][j] = Check(s[i], s[j]);
    }
    // 情况1：首位匹配 + 中间匹配
    if (Check(s[i], s[j]) && Solver(i + 1, j - 1)) {
      return dp[i][j] = 1;
    }
    // 情况2：分割线，左右匹配
    for (int k = i + 1; k < j; k++) {
      if (Solver(i, k) && Solver(k + 1, j)) {
        return dp[i][j] = 1;
      }
    }
    return dp[i][j] = 0;
  }
  int n;
  map<char, vector<int>> charPoss;
  void init() {
    for (int i = 0; i < n; i++) {
      charPoss[s[i]].push_back(i);
    }
  }

 public:
  string lexicographicallySmallestString(string s_) {
    s.swap(s_);
    n = s.size();
    // init();
    dp.resize(n, vector<int>(n, -1));  // dp[i][j] 是否可以被消除
    string ans;
    // if (Solver(0, n - 1)) return ans;
    set<int> pre;
    pre.insert(0);  // 初始状态
    while (!pre.empty()) {
      if (*pre.rbegin() == n) break;
      set<int> now;  // 下一轮状态
      char minChar = 'z' + 1;
      for (auto firstPos : pre) {
        if (Solver(firstPos, n - 1)) {
          MyPrintf("finish firstPos=%d\n", firstPos);
          return ans;
        }
        for (int i = firstPos; i < n; i++) {
          if (!Solver(firstPos, i - 1)) {
            continue;
          }
          MyPrintf("firstPos=%d, i=%d solver=1\n", firstPos, i);
          char c = s[i];
          if (c < minChar) {  // 最小的字符
            minChar = c;
            now.clear();
          }
          if (c == minChar) {  // 相同的字符
            now.insert(i + 1);
          }
        }
      }
      MyPrintf("minChar=%c\n", minChar);
      ans.push_back(minChar);
      pre.swap(now);  // 下一轮状态
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(string s, const string& ans) { TEST_SMP1(Solution, lexicographicallySmallestString, ans, s); }

int main() {
  string ans;
  // Test("abc", "a");
  // Test("bcda", "");
  // Test("zdce", "zdce");
  // Test("igkgligkjgkkhghligggjhkkjgijggjkjlljgjjlijkhkhk", "igkgliggkkhghligggjhkgggjkjlljgjjhk");
  // Test("jjlijkhkhk", "jjhk");
  Test("lijkhkhk", "hk");
  return 0;
}

#endif