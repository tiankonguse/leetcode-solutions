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
    pre = (pre * BASE + (str[i] - 'A' + 1)) % mod1e9;
  }
  return pre;
}
ll Hash(const ll pre, const char c) {
  return (pre * BASE + (c - 'A' + 1)) % mod1e9;
}

char word[200];
const ll maxWord = 10;
const ll batchSize = 1000;
unordered_set<ll> h;
string buf;
vector<ll> dp;
ll ans = 0;
bool first = true;
ll offset = 0;

void CalAns() {
  const ll n = buf.size();
  dp.resize(n + 1, 0);
  if (first) {
    first = false;
    dp[0] = 1;
  }

  for (ll i = 0; i < n; i++) {
    if (dp[i] == 0) continue; // 不可到达
    ans = max(ans, offset + i);
    ll pre = 0;
    for (ll j = 0; j < maxWord && i + j < n; j++) {
      pre = Hash(pre, buf[i + j]);
      if (h.count(pre)) {
        dp[i + j + 1] = 1;  // 下一个位置标记可以到达
        ans=max(ans, offset + i + j + 1);
      }
    }
  }

  // 保留最后 maxWord 个字符 ,不够时，代表计算完了
  if(n <= maxWord){
    return;
  }

  for (int i = 0; i < maxWord; i++) {
    dp[i] = dp[n - maxWord + i];
    buf[i] = buf[n - maxWord + i];
  }
  dp[maxWord] = dp[n];  // 有可能完全匹配，指向 maxWord

  dp.resize(maxWord + 1);
  buf.resize(maxWord);
  offset += n - maxWord;
}

void Add(const char* s) {
  buf.append(s);
  if (buf.size() < batchSize) {
    return;
  }
  CalAns();
}

void Solver() {  //
  while (true) {
    scanf("%s", word);
    if (word[0] == '.') {
      break;
    }
    h.insert(Hash(word, 0, strlen(word)));
  }

  buf.reserve(batchSize);
  while (scanf("%s", word) != EOF) {
    if (word[0] == '.') break;
    Add(word);
  }
  CalAns();
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*



*/