/*
ID: tiankonguse
TASK: road
LANG: C++
CONTEST: CSP-J 2023
OJ: https://qoj.ac/contest/1427/problem/7810
https://www.luogu.com.cn/problem/P9749
https://www.luogu.com.cn/record/220072861
*/
#define TASK "road"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

/*
题目：一条路上n个加油站，告诉你相邻加油站的距离，每个加油站的价格，问车油箱无限大时，从第一个加油站开到最后一个加油站，最少需要多少钱。
*/

vector<ll> v;
vector<ll> a;

void Solver() {  //
  ll n, d;
  scanf("%lld%lld", &n, &d);
  v.resize(n - 1, 0);
  for (int i = 0; i < n - 1; i++) {
    scanf("%lld", &v[i]);
  }

  a.resize(n, 0);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }

  ll ans = 0;
  ll all_dis = 0;  // 总共需要跑的公里数
  ll all_oil = 0;  // 加的总油
  ll pre_min_price = a[0];
  for (int i = 1; i < n; i++) {
    ll dis = v[i - 1];
    all_dis += dis;

    ll need_oil = (all_dis + d - 1) / d;
    if (all_oil < need_oil) {  // 油不够，需要买油
      ll buy_oil = need_oil - all_oil;
      ans += buy_oil * pre_min_price;
      all_oil += buy_oil;
    }
    pre_min_price = min(pre_min_price, a[i]);
  }

  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5 4
10 10 10 10
9 8 9 6 5

79
*/