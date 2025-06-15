
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
  bool IsChar(char c) { return c >= 'a' && c <= 'z'; }
  char ToChar(char c) {
    if (c >= 'a' && c <= 'z') {
      return c;
    }
    if (c >= 'A' && c <= 'Z') {
      return c - 'A' + 'a';
    }
    return ' ';
  }
  vector<string> words;
  void SplitWord(const string& caption) {
    words.clear();
    string word;
    for (auto c : caption) {
      c = ToChar(c);
      if (IsChar(c)) {
        word.push_back(c);
      } else {
        if (word.size() > 0) {
          words.push_back(word);
          word.clear();
        }
      }
    }
    if (word.size() > 0) {
      words.push_back(word);
      word.clear();
    }
  }

 public:
  string generateTag(const string& caption) {
    string ans;
    ans.push_back('#');
    bool isFirstWord = true;
    SplitWord(caption);
    for (auto& word : words) {
      if (isFirstWord) {
        isFirstWord = false;
      } else {
        word[0] = word[0] - 'a' + 'A';
      }
      ans.append(word);
    }
    if (ans.size() > 100) {
      ans.resize(100);
    }
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