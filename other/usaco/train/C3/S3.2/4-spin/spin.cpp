/*
ID: tiankonguse
TASK: spin
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "spin"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
#endif
}

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

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; (t = x % y); x = y, y = t);
  return y;
}

vector<ll> speeds;
vector<vector<pair<ll, ll>>> nums;
vector<pair<ll, ll>> ps;
ll num = 0;

bool Check(ll t) {
  ps.reserve(num);
  ps.clear();
  for (size_t i = 0; i < nums.size(); i++) {
    const ll offset = (speeds[i] * t) % 360;
    for (auto [s, r] : nums[i]) {
      ll L = (s + offset) % 360;
      ll R = (L + r) % 360;
      if (L <= R) {
        ps.push_back({L, +1});
        ps.push_back({R + 1, -1});
      } else {
        ps.push_back({L, +1});
        ps.push_back({360, -1});
        ps.push_back({0, +1});
        ps.push_back({R + 1, -1});
      }
    }
  }
  sort(ps.begin(), ps.end());

  ll sum = 0;
  for (auto [L, add] : ps) {
    sum += add;
    if (sum == 5) {
      return true;
    }
  }
  return false;
}

void Solver() {  //
  speeds.resize(5);
  nums.resize(5);
  ll w;
  for (int i = 0; i < 5; i++) {
    scanf("%lld%lld", &speeds[i], &w);
    nums[i].resize(w);
    num += w;
    for (int j = 0; j < w; j++) {
      scanf("%lld%lld", &nums[i][j].first, &nums[i][j].second);
    }
  }

  for (ll t = 0; t <= 360; t++) {
    if (Check(t)) {
      printf("%lld\n", t);
      return;
    }
  }
  printf("none\n");
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/