/*
ID: tiankonguse
TASK: kimbits
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "kimbits"

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

ll N, L, I;
ll dp[33][33];

ll Dfs(int n, int l) {
  if (n < 0) return 1;
  ll& ret = dp[n][l];
  if (ret != -1) return ret;
  if (l == 0) return ret = 1;                   // [0,0]
  if (n + 1 <= l) return ret = 1LL << (n + 1);  // [0, 2^n-1]
  return ret = Dfs(n - 1, l - 1) + Dfs(n - 1, l);
}

void Solver() {  //
  scanf("%lld%lld%lld", &N, &L, &I);
  memset(dp, -1, sizeof(dp));

  string ans;
  ans.reserve(N);
  ll l = L;
  ll p = I;
  for (int i = N - 1; i >= 0; i--) {
    ll zeroNum = Dfs(i - 1, l);  // 尝试选择 0
    if (zeroNum >= p) {
      ans.push_back('0');
    } else {
      ans.push_back('1');
      p -= zeroNum;
      l--;
    }
  }
  printf("%s\n", ans.data());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/