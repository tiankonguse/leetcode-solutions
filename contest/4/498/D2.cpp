
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
  string SL, SR;
  ll cache[17][11][2][2];
  ll Dfs(int pos, int preSelectVal, bool limitDown, bool limitUp) {
    if (pos == 16) {
      return 1;
    }
    if (cache[pos][preSelectVal][limitDown][limitUp] != -1) {
      return cache[pos][preSelectVal][limitDown][limitUp];
    }
    int down = limitDown ? SL[pos] - '0' : 0;
    int up = limitUp ? SR[pos] - '0' : 9;
    ll ret = 0;
    for (int val = down; val <= up; val++) {
      if (IsInpath[pos]) {
        if (val >= preSelectVal) {
          ret += Dfs(pos + 1, val, limitDown && val == down, limitUp && val == up);
        }
      } else {
        ret += Dfs(pos + 1, preSelectVal, limitDown && val == down, limitUp && val == up);
      }
    }
    return cache[pos][preSelectVal][limitDown][limitUp] = ret;
  }
  string ToStr(ll x) {
    string ret = to_string(x);
    std::reverse(ret.begin(), ret.end());
    if (ret.size() < 16) {
      ret.resize(16, '0');
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }

 public:
  long long countGoodIntegersOnPath(long long l, long long r, string directions) {
    InitPath(directions);
    SL = ToStr(l);
    SR = ToStr(r);
    memset(cache, -1, sizeof(cache));
    return Dfs(0, 0, true, true);
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