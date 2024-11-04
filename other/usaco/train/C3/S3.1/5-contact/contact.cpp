/*
ID: tiankonguse
TASK: contact
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "contact"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const ll M = 100;
ll A, B, N;

unordered_map<string, ll> h;

string buf;
char str[100];

void Add(char c) {
  buf.push_back(c);
  for (ll i = A; i <= B; i++) {
    const ll len = buf.size();
    if (len < i) break;
    h[buf.substr(len - i)]++;
  }

  if (buf.size() == M) {
    buf = buf.substr(buf.size() - B);
  }
}

void Solver() {  //
  scanf("%lld%lld%lld", &A, &B, &N);
  buf.reserve(M);

  while (~scanf("%s", str)) {
    const char* p = str;
    while (*p) {
      Add(*p);
      p++;
    }
  }

  // 获取最高的 N 个频次
  map<ll, ll> freqN;
  for (const auto& [s, freq] : h) {
    freqN[freq]++;
    if (ll(freqN.size()) > N) {
      freqN.erase(freqN.begin());
    }
  }

  ll minFreq = inf;
  vector<pair<ll, ll>> reqs;
  unordered_map<ll, ll> H;
  vector<vector<string>> ans;
  reqs.reserve(N);
  ans.reserve(N);
  for (auto it = freqN.rbegin(); it != freqN.rend(); it++) {
    reqs.push_back(*it);
    ans.push_back({});
    H[it->first] = reqs.size() - 1;
    ans.back().reserve(it->second);
    minFreq = min(minFreq, it->first);
  }
  for (const auto& [s, freq] : h) {
    if (freq < minFreq) continue;
    ans[H[freq]].push_back(s);
  }

  for (size_t i = 0; i < reqs.size(); i++) {
    printf("%lld\n", reqs[i].first);
    sort(ans[i].begin(), ans[i].end(), [](auto& a, auto& b) {
      if (a.size() == b.size()) {
        return a < b;
      } else {
        return a.size() < b.size();
      }
    });
    for (size_t j = 0; j < ans[i].size(); j++) {
      printf("%s", ans[i][j].data());
      if (j % 6 == 5 || j + 1 == ans[i].size()) {
        printf("\n");
      } else {
        printf(" ");
      }
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/