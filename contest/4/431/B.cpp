
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
  ll calculateScore(const string& s) {
    vector<vector<int>> g(27);

    int n = s.size();
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int v = s[i] - 'a';
      int V = 25 - v;
      if (g[V].empty()) {
        g[v].push_back(i);
      }else{
        ans += i - g[V].back();
        g[V].pop_back();
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

#endif©leetcode