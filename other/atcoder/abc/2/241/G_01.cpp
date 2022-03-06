#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;
// using mint = modint998244353;
using mint = modint1000000007;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using tlll = tuple<ll, ll, ll>;
constexpr ll INF = 1LL << 60;
template <class T>
bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T>
bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
ll safemod(ll A, ll M) { return (A % M + M) % M; }
ll divfloor(ll A, ll B) {
  if (B < 0) {
    return divfloor(-A, -B);
  }
  return (A - safemod(A, B)) / B;
}
ll divceil(ll A, ll B) {
  if (B < 0) {
    return divceil(-A, -B);
  }
  return divfloor(A + B - 1, B);
}
template <class T>
void unique(vector<T> &V) {
  V.erase(unique(V.begin(), V.end()), V.end());
}
template <class T>
void sortunique(vector<T> &V) {
  sort(V.begin(), V.end());
  V.erase(unique(V.begin(), V.end()), V.end());
}
#define FINALANS(A)      \
  do {                   \
    cout << (A) << '\n'; \
    exit(0);             \
  } while (false)
template <class T>
void printvec(vector<T> &V) {
  int _n = V.size();
  for (int i = 0; i < _n; i++) cout << V[i] << (i == _n - 1 ? '\n' : ' ');
}
template <class T>
void printvect(vector<T> &V) {
  for (auto v : V) cout << v << '\n';
}
template <class T>
void printvec2(vector<vector<T>> &V) {
  for (auto &v : V) printvec(v);
}

#include <atcoder/maxflow>

bool isok(ll N, vector<vector<ll>> &S, ll x) {
  vector<vector<ll>> T(N, vector<ll>(N));
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      T.at(i).at(j) = S.at(i).at(j);
    }
  }

  for (ll i = 0; i < N; i++) {
    if (i == x) continue;
    if (T.at(x).at(i) != -1) continue;
    T.at(x).at(i) = 1;
    T.at(i).at(x) = 0;
  }

  vector<pll> rounds;
  vector<ll> wins(N, 0);
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      if (T.at(i).at(j) == 1) wins.at(i)++;
      if (i < j && T.at(i).at(j) == -1) rounds.push_back(make_pair(i, j));
    }
  }
  ll K = rounds.size();

  mf_graph<ll> gr(1 + N + K + 1);
  for (ll i = 0; i < N; i++) {
    if (i == x) continue;
    ll w = wins.at(x) - wins.at(i) - 1;
    if (w < 0) return false;
    gr.add_edge(0, 1 + i, w);
  }
  for (ll k = 0; k < K; k++) {
    auto [i, j] = rounds.at(k);
    gr.add_edge(1 + i, 1 + N + k, 1);
    gr.add_edge(1 + j, 1 + N + k, 1);
    gr.add_edge(1 + N + k, 1 + N + K, 1);
  }

  ll fl = gr.flow(0, 1 + N + K);
  return fl == K;
}

int main() {
  ll N, M;
  cin >> N >> M;
  vector<vector<ll>> S(N, vector<ll>(N, -1));
  for (ll i = 0; i < M; i++) {
    ll w, l;
    cin >> w >> l;
    w--, l--;
    S.at(w).at(l) = 1;
    S.at(l).at(w) = 0;
  }

  vector<ll> ans;
  for (ll i = 0; i < N; i++) {
    if (isok(N, S, i)) ans.push_back(i + 1);
  }
  printvec(ans);
}