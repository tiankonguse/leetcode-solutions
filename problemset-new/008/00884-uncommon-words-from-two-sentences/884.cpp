
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
class Solution {
 public:
  vector<string> uncommonFromSentences(const string& s1, const string& s2) {
    unordered_map<string, int> mp1, mp2;
    auto Trans = [](const string& s, unordered_map<string, int>& mp) {
      string buf;
      for (auto c : s) {
        if (c == ' ') {
          if (!buf.empty()) mp[buf]++;
          buf.clear();
        } else {
          buf.push_back(c);
        }
      }
      if (!buf.empty()) mp[buf]++;
      buf.clear();
    };
    Trans(s1, mp1);
    Trans(s2, mp2);

    vector<string> ans;
    for (auto& [k, v] : mp1) {
      if (v == 1 && mp2.count(k) == 0) {
        ans.push_back(k);
      }
    }
    for (auto& [k, v] : mp2) {
      if (v == 1 && mp1.count(k) == 0) {
        ans.push_back(k);
      }
    }
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