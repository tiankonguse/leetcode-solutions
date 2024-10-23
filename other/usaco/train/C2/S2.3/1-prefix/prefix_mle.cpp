/*
ID: tiankonguse
TASK: prefix
LANG: C++
*/
#define TASK "prefix"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;
ll Hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'A' + 1)) % mod1e7;
  }
  return pre;
}
ll Hash(const ll pre, const char c) {
  return (pre * BASE + (c - 'A' + 1)) % mod1e7;
}

char primitive[20];
ll maxLen = 0;
string S;
ll len;
unordered_set<ll> h;
vector<ll> dp;

ll Dfs(ll pos) {
  if (pos == len) return 0;
  ll& ret = dp[pos];
  if (ret != -1) return ret;

  ret = 0;
  ll pre = 0;
  for (ll i = 0; i < maxLen && pos + i < len; i++) {
    pre = Hash(pre, S[pos + i]);
    if (h.count(pre)) {
      ret = max(ret, (i + 1) + Dfs(pos + i + 1));
    }
  }
  return ret;
}

void Solver() {  //
  while (true) {
    scanf("%s", primitive);
    if (primitive[0] == '.') {
      break;
    }
    // printf("in: %s\n", primitive);
    ll l = strlen(primitive);
    maxLen = max(maxLen, l);
    h.insert(Hash(primitive, 0, l));
  }
  // printf("in end\n");

  S.reserve(200001);
  char s[100];
  while (scanf("%s", s) != EOF) {
    if (s[0] == '.') break;
    S.append(s);
  }
  len = S.size();
  dp.resize(len+1, -1);
  printf("%lld\n", Dfs(0));
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*



*/