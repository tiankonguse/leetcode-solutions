
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  int k;

 public:
   // 思路：枚举，然后使用滑动窗口，保证窗口内的字符个数不超过 k，且相邻字符距离不大于 2，且第一个字符是枚举字符
   // 封装数据结构：可以统计字符个数、以及超过 k 的字符个数
  int countCompleteSubstrings(const string& word, int k) {
    this->k = k;
    int ans = 0;
    set<char> charSet(word.begin(), word.end());
    for (auto c : charSet) {
      ans += countCompleteSubstrings(word, k, c);
    }
    return ans;
  }
  inline int Dis(int a, int b) {
    if (a > b) {
      return a - b;
    } else {
      return b - a;
    }
  };
  vector<int> charCount;
  int kNum = 0;
  int charNum = 0;
  void Init() {
    kNum = 0;
    charNum = 0;
    charCount.clear();
    charCount.resize(26, 0);
  }
  void Add(char c) {
    int v = c - 'a';
    if (charCount[v] == 0) {
      charNum++;
    }
    charCount[v]++;
    if (charCount[v] == k) {
      kNum++;
    }
  }
  void Remove(char c) {
    int v = c - 'a';
    if (charCount[v] == k) {
      kNum--;
    }
    charCount[v]--;
    if (charCount[v] == 0) {
      charNum--;
    }
  }
  int countCompleteSubstrings(const string& word, const int k, const char c) {
    int ans = 0;
    int n = word.size();
    int left = 0;
    Init();

    // 第一个字符必须是 c
    // 先找到第 k 个 c
    // 如果期间，其他字符出现次数超过 k，则需要跳过第一个 c，找到下个 c
    // 如果期间，相邻字符距离大于 2，则需要跳过第一个 c，找到下个 c
    for (int right = 0; right < n; right++) {
      Add(word[right]);

      while (charCount[word[right] - 'a'] > k                            // 保证所有字符个数不超过 k
             || (right >= left && word[left] != c)                       // 保证第一个字符是 c
             || (right > left && Dis(word[right], word[right - 1]) > 2)  // 保证相邻距离不大于 2
      ) {
        Remove(word[left]);
        left++;
      }

      if (left > right) continue;
      if (kNum > 0 && kNum == charNum && (right - left + 1) == kNum * k) {
        ans++;
      }
    }
    // MyPrintf("ans=%d\n", ans);

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif