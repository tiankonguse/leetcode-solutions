// by SmileMask
#include <bits/stdc++.h>
using namespace std;

namespace SmileMask {
#define rd read()
// #define int long long
typedef long long ll;
int read() {
  int num = 0, sign = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') sign = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    num = (num << 3) + (num << 1) + ch - '0';
    ch = getchar();
  }
  return num * sign;
}

const int N = 2e5 + 10;
const ll mod = 1e9 + 7;
const ll base = 233;
const int M = 5e6 + 10;

ll qmi(ll x, int y) {
  ll res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return res;
}

string S[N][2], T[N][2];
int lenS[N][2], lenT[N][2];

int n, m;

vector<ll> HashS[N][2], HashT[N][2];
ll pw[M];

ll get(int l, int r, vector<ll> &h) {
  if (l == 0 || r == 0) return 0;
  if (l > r) return 0;
  return (h[r] - h[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

vector<pair<string, string>> SS[N];

struct node {
  string T0, T1;
  int idx;
};
vector<node> TT[N];

unordered_map<ll, int> idx;
int tot;
int ans[N];

struct trie {
  int tot = 1, L[M * 2], R[M * 2], ti;
  unordered_map<char, int> ch[M * 2];
  void init() {
    for (int i = 1; i <= tot; i++) ch[i].clear(), L[i] = R[i] = 0;
    tot = 1, ti = 0;
  }

  int insert(string &s) {
    int u = 1;
    for (int i = 0; i < s.size(); i++) {
      int &p = ch[u][s[i] - 'a'];
      if (!p) p = ++tot;
      u = p;
    }
    return u;
  }

  void dfs(int u) {
    if (!u) return;
    L[u] = ++ti;
    for (int i = 0; i < 26; i++) dfs(ch[u][i]);
    R[u] = ti;
  }
} T1, T2;

pair<int, int> posS[N], posT[N];

struct fenwick {
  int t[M], n;

  void init(int _n) {
    n = _n, fill_n(t, n + 3, 0);
    return;
  }

  void add(int x, int v) {
    while (x <= n) t[x] += v, x += (x & (-x));
  }

  void add(int x, int y, int v) { add(y + 1, -v), add(x, v); }
  int ask(int x) {
    int res = 0;
    while (x) res += t[x], x -= (x & (-x));
    return res;
  }
} Tree;

void solve(vector<pair<string, string>> &S, vector<node> &T) {
  for (int i = 0; i < S.size(); i++) {
    auto &e = S[i];
    posS[i].second = T2.insert(e.second);
    reverse(e.first.begin(), e.first.end());
    posS[i].first = T1.insert(e.first);
  }
  for (int i = 0; i < T.size(); i++) {
    auto &e = T[i];
    posT[i].second = T2.insert(e.T1);
    reverse(e.T0.begin(), e.T0.end());
    posT[i].first = T1.insert(e.T0);
  }
  T1.dfs(1), T2.dfs(1);
  Tree.init(T2.ti);
  vector<vector<array<int, 3>>> vec;
  vec.resize(T1.ti + 3);
  for (int i = 0; i < S.size(); i++)
    vec[T1.L[posS[i].first]].push_back({T2.L[posS[i].second], T2.R[posS[i].second], 1}),
        vec[T1.R[posS[i].first] + 1].push_back({T2.L[posS[i].second], T2.R[posS[i].second], -1});
  for (int i = 0; i < T.size(); i++) vec[T1.L[posT[i].first]].push_back({T2.L[posT[i].second], -1, T[i].idx});
  for (int i = 1; i <= T1.ti; i++) {
    for (auto &e : vec[i]) {
      if (e[1] != -1) {
        Tree.add(e[0], e[1], e[2]);
      }
    }
    for (auto &e : vec[i]) {
      if (e[1] == -1) {
        ans[e[2]] = Tree.ask(e[0]);
      }
    }
  }
  T1.init(), T2.init();
}

void Main() {
  n = rd, m = rd, pw[0] = 1;
  for (int i = 1; i < M; i++) pw[i] = pw[i - 1] * base % mod;
  for (int i = 1; i <= n; i++) cin >> S[i][0] >> S[i][1], lenS[i][0] = S[i][0].size(), lenS[i][1] = S[i][1].size();
  for (int i = 1; i <= m; i++) {
    cin >> T[i][0] >> T[i][1], lenT[i][0] = T[i][0].size(), lenT[i][1] = T[i][1].size();
  }
  for (int i = 1; i <= n; i++) {
    S[i][0] = " " + S[i][0], S[i][1] = " " + S[i][1];
    assert(S[i][0] == S[i][1]);
    HashS[i][0].resize(S[i][0].size());
    HashS[i][1].resize(S[i][1].size());
    for (int j = 1; j <= lenS[i][0]; j++) HashS[i][0][j] = (HashS[i][0][j - 1] * base % mod + S[i][0][j]) % mod;
    for (int j = 1; j <= lenS[i][1]; j++) HashS[i][1][j] = (HashS[i][1][j - 1] * base % mod + S[i][1][j]) % mod;
  }
  for (int i = 1; i <= m; i++) {
    T[i][0] = " " + T[i][0], T[i][1] = " " + T[i][1];
    HashT[i][0].resize(T[i][0].size());
    HashT[i][1].resize(T[i][1].size());
    for (int j = 1; j <= lenT[i][0]; j++) HashT[i][0][j] = (HashT[i][0][j - 1] * base % mod + T[i][0][j]) % mod;
    for (int j = 1; j <= lenT[i][1]; j++) HashT[i][1][j] = (HashT[i][1][j - 1] * base % mod + T[i][1][j]) % mod;
  }
  {
    for (int i = 1; i <= n; i++) {
      int p = 0, q = lenS[i][0] + 1;
      while (S[i][0][p + 1] == S[i][1][p + 1]) p++;
      while (S[i][0][q - 1] == S[i][1][q - 1]) q--;
      if (p + 1 >= q) continue;
      ll x = get(p + 1, q - 1, HashS[i][0]), y = get(p + 1, q - 1, HashS[i][1]);
      ll z = (x * pw[M - 1] % mod + y) % mod;
      if (!idx.count(z)) idx[z] = ++tot;
      SS[idx[z]].push_back({S[i][0].substr(1, p), S[i][1].substr(q, lenS[i][0] - q + 1)});
    }
    for (int i = 1; i <= m; i++) {
      if (lenT[i][0] != lenT[i][1]) {
        ans[i] = 0;
        continue;
      }
      int p = 0, q = lenT[i][0] + 1;
      while (T[i][0][p + 1] == T[i][1][p + 1]) p++;
      while (T[i][0][q - 1] == T[i][1][q - 1]) q--;
      if (p + 1 >= q) continue;
      ll x = get(p + 1, q - 1, HashT[i][0]), y = get(p + 1, q - 1, HashT[i][1]);
      ll z = (x * pw[M - 1] % mod + y) % mod;
      if (!idx.count(z)) idx[z] = ++tot;
      TT[idx[z]].push_back({T[i][0].substr(1, p), T[i][1].substr(q, lenT[i][0] - q + 1), i});
    }
  }
  for (int i = 1; i <= tot; i++) {
    if (!SS[i].size() || !TT[i].size()) {
      for (node &t : TT[i]) ans[t.idx] = 0;
      continue;
    }
    solve(SS[i], TT[i]);
  }
  for (int i = 1; i <= m; i++) cout << ans[i] << endl;
}
}  // namespace SmileMask

signed main() {
  freopen("replace.in", "r", stdin);
  freopen("replace.out", "w", stdout);
  SmileMask::Main();
  return 0;
}
/*

结束了

*/
