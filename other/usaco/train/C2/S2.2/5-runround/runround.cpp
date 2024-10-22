/*
ID: tiankonguse
TASK: runround
LANG: C++
*/
#define TASK "runround"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
bool check(const ll n) {
  string s = to_string(n);
  ll len = s.size();
  vector<ll> flag(10, 0);
  for (auto c : s) {
    ll v = c - '0';
    if (v == 0 || flag[v]) {
      // printf("n=%lld v==0||double [%lld]\n", n, v);
      return false;
    }
    flag[v] = 1;
  }

  ll num = 0;
  ll index = 0;
  flag.clear();
  flag.resize(10, 0);
  while (!flag[index]) {
    ll v = s[index] - '0';
    flag[index] = 1;
    num++;
    index = (index + v) % len;
  }

  // printf("n=%lld num=%lld len=%lld\n", n, num, len);
  return num == len && index == 0;
}
void Solver() {  //
  ll n;
  scanf("%lld", &n);

  n++;
  // ll loop = 0;
  while (!check(n)) {
    n++;
    // loop++;
    // if (loop > 80) break;
  }

  printf("%lld\n", n);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
81362
13628136
281362
81
3
628


99
100
123
2
31


142
4
2142
14



*/