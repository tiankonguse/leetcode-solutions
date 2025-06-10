
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
  string word1, word2;
  int n;
  vector<int> dp;
  vector<vector<int>> dpRange;
  int Dfs(int p) {
    if (p == 0) return 0;
    if (dp[p] != -1) return dp[p];
    int& ret = dp[p];
    if (p == 1) {
      if (word1[0] == word2[0]) {
        ret = 0;
      } else {
        ret = 1;
      }
      return ret;
    }
    // 枚举后缀长度
    ret = DfsRange(1, p);
    for (int i = 1; i < p; i++) {  // [1, i] [i+1, p]
      ret = min(ret, Dfs(i) + DfsRange(i + 1, p));
    }

    return ret;
  }
  int DfsRange(int l, int r) {
    if (dpRange[l][r] != -1) return dpRange[l][r];
    int& ret = dpRange[l][r];
    int lr = r - l + 1;
    ret = Solver(l, r);  // 尝试不翻转

    // 先尝试翻转
    std::reverse(word1.begin() + l - 1, word1.begin() + r);
    ret = min(ret, Solver(l, r) + 1);
    std::reverse(word1.begin() + l - 1, word1.begin() + r);
    return ret;
  }
  int dict[26][26];
  int Solver(int l, int r) {
    memset(dict, 0, sizeof(dict));
    int swapNum = 0;
    int diffNum = 0;
    for (int i = l; i <= r; i++) {
      int c1 = word1[i - 1] - 'a';
      int c2 = word2[i - 1] - 'a';
      if (c1 == c2) {
        continue;
      }
      diffNum++;
      dict[c1][c2]++;
      if (dict[c2][c1]) {
        swapNum++;  // 交换
        dict[c1][c2]--;
        dict[c2][c1]--;
      }
    }
    return diffNum - swapNum;
  }

 public:
  int minOperations(string word1_, string word2_) {
    word1.swap(word1_);
    word2.swap(word2_);
    n = word1.size();
    dp.resize(n + 1, -1);
    dpRange.resize(n + 1, vector<int>(n + 1, -1));
    if (word1 == word2) return 0;
    return Dfs(n);
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