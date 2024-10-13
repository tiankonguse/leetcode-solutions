// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const int N = 1010;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const string FWE = "FWE";
ll FWE_N = 3;
class Solution {
  vector<vector<vector<ll>>> dp;
  unordered_map<char, int> H;
  vector<ll> nextVal;
  vector<ll> V;
  ll n;
  void Init(const string& s) {
    FWE_N = FWE.size();
    nextVal.resize(FWE_N);
    for (ll i = 0; i < FWE_N; i++) {
      H[FWE[i]] = i;
      nextVal[i] = i + 1;
    }
    nextVal[FWE_N - 1] = 0;

    n = s.size();
    V.resize(n);
    for (ll i = 0; i < n; i++) {
      V[i] = H[s[i]];
    }

    dp.resize(4, vector<vector<ll>>(n + 1, vector<ll>(2 * N, -1)));
  }
  ll P(const ll minScore) { return minScore + N; }
  ll Cal(const ll aliceVal, const ll bobVal) {
    if (nextVal[aliceVal] == bobVal) {
      return 1;  // 得一分
    } else if (nextVal[bobVal] == aliceVal) {
      return -1;  // 扣一分
    } else {
      return 0;
    }
  }
  // minScore 允许是负数，代表可以输几分， 使用 P() 函数映射到数组
  ll Dfs(const ll p, const ll minScore, const ll preBobVal) {
    if (p < 0) {
      if (minScore <= 0) {
        return 1;
      } else {
        return 0;
      }
    }
    ll& ret = dp[preBobVal][p][P(minScore)];
    if (ret != -1) return ret;
    const ll aliceVal = V[p];

    ret = 0;
    for (ll bobVal = 0; bobVal < 3; bobVal++) {
      if (bobVal == preBobVal) continue;  // 不能选择一样的
      const ll score = Cal(aliceVal, bobVal);
      ret = (ret + Dfs(p - 1, minScore - score, bobVal)) % mod;
    }
    return ret;
  }

 public:
  int countWinningSequences(const string& s) {
    Init(s);
    return Dfs(n - 1, 1, 3);
  }
};