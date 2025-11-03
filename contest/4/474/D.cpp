
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
  vector<int> charCount;
  char oddVal = ' ';
  bool IsPalindromic(char& oddVal) const {
    int odd = 0;
    for (int i = 0; i < 26; i++) {
      if (charCount[i] % 2 == 1) {
        odd++;
        oddVal = i + 'a';
      }
    }
    return odd <= 1;
  }

  string ans;
  int n;
  bool HasAns(const string& target) const {
    // 构造最大的字典序回文串
    string buf(n, oddVal);
    int l = 0, r = n - 1;
    for (int i = 25; i >= 0; i--) {
      int useCount = 0;
      while (charCount[i] > useCount) {
        useCount += 2;
        buf[l++] = buf[r--] = 'a' + i;
      }
    }
    return buf > target;
  }

  bool Dfs(int l, int r, const string& target) {
    if (l >= r) {
      return ans > target;
    }
    const int cIdx = target[l] - 'a';
    if (charCount[cIdx] > 0) {
      charCount[cIdx] -= 2;
      ans[l] = ans[r] = target[l];
      if (Dfs(l + 1, r - 1, target)) {
        return true;
      }
      charCount[cIdx] += 2;
    }
    
    // 尝试设置为大于 target[l] 的最小字符
    for (int i = cIdx + 1; i < 26; i++) {
      if (charCount[i] == 0) continue;
      charCount[i] -= 2;
      ans[l++] = ans[r--] = 'a' + i;
      return BuildMinAns(l, r);
    }
    return false; // 无法构造,需要回溯
  }
  bool BuildMinAns(int l, int r) {
    // 第二步：贪心构造剩余部分的最小字典序回文串
    for (int j = 0; j < 26; j++) {
      while (charCount[j] > 0) {
        charCount[j] -= 2;
        ans[l++] = ans[r--] = 'a' + j;
      }
    }
    return true;
  }

 public:
  string lexPalindromicPermutation(const string& s, const string& target) {
    n = s.size();
    charCount.resize(26, 0);
    for (char c : s) {
      charCount[c - 'a']++;
    }
    if (!IsPalindromic(oddVal)) {
      MyPrintf("no palindromic permutation\n");
      return "";
    }
    ans.resize(n, ' ');
    if (oddVal != ' ') {
      ans[n / 2] = oddVal;
      charCount[oddVal - 'a']--;
    }
    if (!HasAns(target)) {
      MyPrintf("no ans\n");
      return "";
    }
    // 贪心构造大于 target 的最小回文串
    Dfs(0, n - 1, target);
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