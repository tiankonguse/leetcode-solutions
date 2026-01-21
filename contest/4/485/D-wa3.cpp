
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
  string lexSmallestAfterDeletion(string s) {
    string ans;
    vector<int> counts(26, 0);
    for (auto c : s) {
      while (ans.size() > 0 && ans.back() > c && counts[ans.back() - 'a'] > 1) {
        counts[ans.back() - 'a']--;
        ans.pop_back();
      }
      ans.push_back(c);
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