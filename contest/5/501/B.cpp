
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
  vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {
    unordered_map<string, int> cnt;
    string s;
    auto Flush = [&]() {
      if (!s.empty() && s.back() == '-') {
        s.pop_back();
      }
      if (!s.empty()) {
        cnt[s]++;
        s.clear();
      }
    };
    auto Add = [&](char c) {
      if (c == ' ') {
        Flush();
      } else if (c == '-') {
        if (!s.empty() && s.back() == '-') {
          s.push_back(c);
        } else {
          Flush();
        }
      } else {
        s.push_back(c);
      }
    };
    for (auto& chunk : chunks) {
      for (auto c : chunk) {
        Add(c);
      }
    }
    Flush();
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      ans.push_back(cnt[q]);
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