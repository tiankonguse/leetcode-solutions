
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
  vector<int> IsInpath;
  void InitPath(const string& directions) {
    IsInpath.resize(16, 0);
    int r = 0, c = 0;
    IsInpath[r * 4 + c] = 1;
    for (char ch : directions) {
      if (ch == 'D') {
        r++;
      } else {
        c++;
      }
      IsInpath[r * 4 + c] = 1;
    }
  }
  string s;
  ll cache[17][11][2];
  ll Dfs(int pos, int preSelectVal, bool limit) {
    if (pos == 16) {
      return 1;
    }
    if (cache[pos][preSelectVal][limit] != -1) {
      return cache[pos][preSelectVal][limit];
    }
    int up = limit ? s[pos] - '0' : 9;
    ll ret = 0;
    for (int val = 0; val <= up; val++) {
      if (IsInpath[pos]) {
        if (val >= preSelectVal) {
          ret += Dfs(pos + 1, val, limit && val == up);
        }
      } else {
        ret += Dfs(pos + 1, preSelectVal, limit && val == up);
      }
    }
    return cache[pos][preSelectVal][limit] = ret;
  }
  ll Solver(ll x) {
    s = to_string(x);
    std::reverse(s.begin(), s.end());
    if (s.size() < 16) {
      s.resize(16, '0');
    }
    std::reverse(s.begin(), s.end());
    memset(cache, -1, sizeof(cache));
    return Dfs(0, 0, true);
  }

 public:
  long long countGoodIntegersOnPath(long long l, long long r, string directions) {
    InitPath(directions);
    return Solver(r) - Solver(l - 1);
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