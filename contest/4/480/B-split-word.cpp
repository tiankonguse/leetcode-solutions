
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
    vector<pair<string, int>> ws;             //  word, vowelCnt
    // s 是空格分隔的单次列表
    int n = s.size();
    int cnt = 1;
    for (int i = 0; i < n; i++) {
      if (s[i] == ' ') {
        cnt++;
      }
    }
    ws.reserve(cnt );

    // 按空格分割单词
    string word;
    int vowelCnt = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == ' ') {
        ws.push_back({word, vowelCnt});
        vowelCnt = 0;
        word.clear();
      } else {
        word.push_back(s[i]);
        if (h.count(s[i])) {
          vowelCnt++;
        }
      }
    }
    ws.push_back({word, vowelCnt});

    // 反转单词
    s.clear();

    vowelCnt = ws[0].second;
    s.append(ws[0].first);
    for (int i = 1; i < cnt; i++) {
      s.push_back(' ');
      if (ws[i].second == vowelCnt) {
        std::reverse(ws[i].first.begin(), ws[i].first.end());
      }
      s.append(ws[i].first);
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