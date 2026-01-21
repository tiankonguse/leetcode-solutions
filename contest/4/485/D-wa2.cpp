
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
  map<char, vector<int>> links;  // pos 逆序
  bool Check(char c) {           //
    int minPos = links[c].back();
    for (const auto& [c, pos] : links) {
      if (pos.front() < minPos) {
        return false;
      }
    }
    return true;
  };

 public:
  string lexSmallestAfterDeletion(string s) {
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
      links[s[i]].push_back(i);
    }

    string ans;
    while (!links.empty()) {
      int ansPos = -1;
      for (char c = 'a'; c <= 'z'; c++) {  // 枚举下个字符是否可以是 c
        if (links.count(c) == 0) continue;
        if (Check(c)) {
          ans.push_back(c);
          ansPos = links[c].back();
          break;
        }
      }
      for (char c = 'a'; c <= 'z'; c++) {
        if (links.count(c) == 0) continue;
        while (links[c].size() > 0 && links[c].back() <= ansPos) {
          links[c].pop_back();
        }
        if (links[c].empty()) {
          links.erase(c);
        }
      }
    }

    vector<int> counts(26, 0);
    for (auto c : ans) {
      counts[c - 'a']++;
    }
    while (!ans.empty()) {
      char c = ans.back();
      if (counts[c - 'a'] > 1) {
        ans.pop_back();
        counts[c - 'a']--;
      } else {
        break;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& s, const string& ans) {  //
  TEST_SMP1(Solution, lexSmallestAfterDeletion, ans, s);
}

int main() {
  Test("aaccb", "aacb");
  return 0;
}

#endif