
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
  int kSimilarity(string s1, const string& s2) {
    if (s1 == s2) return 0;
    int n = s1.size();

    unordered_map<string, int> h;
    queue<pair<string, int>> que;
    que.push({s1, 0});
    h[s1] = 0;
    while (!que.empty()) {
      auto [s, i] = que.front();
      que.pop();
      const int cost = h[s];
      for (; i < n; i++) {
        if (s[i] != s2[i]) break;
      }

      for (int j = i + 1; j < n; j++) {
        if (s[j] == s2[i]) {
          swap(s[j], s[i]);
          if (h.count(s) == 0) {
            if (s == s2) {
              return cost + 1;
            }
            h[s] = cost + 1;
            que.push({s, i + 1});
          }
          swap(s[j], s[i]);
        }
      }
    }
    return -1;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(string s1, string s2, const int& ans) {
  TEST_SMP2(Solution, kSimilarity, ans, s1, s2);
}

int main() {
  Test("ab", "ba", 1);
  Test("abc", "bca", 2);
  return 0;
}

#endif