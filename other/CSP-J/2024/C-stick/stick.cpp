/*
ID: tiankonguse
TASK: stick
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11229?contestId=209924
*/
#define TASK "stick"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

void Dump(ll val, ll b) {
  if (val) {
    printf("%lld", val);
  }
  for (ll i = 0; i < b; i++) {
    printf("8");
  }
  printf("\n");
}

/*
0: 6
1: 2
2: 5
3: 5
4: 4
5: 5
6: 6
7: 3
8: 7
9: 6

2: 1
3: 7
4: 4
5: 2, 3, 5
6: 0, 6, 9
7: 8

每一位用的火柴越多，数字位数越少。
*/
ll one[] = {-1, -1, 1, 7, 4, 2, 6, 8, 10, 18, 22, 20};
void Solver() {  //
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll a = n % 7;
    ll b = n / 7;
    if (n < 11) {
      printf("%lld\n", one[n]);
      continue;
    }

    if (a == 0) {  // 整除，此时 b 肯定大于0
      Dump(0, b);
    } else if (a == 1) {
      Dump(10, b - 1);
    } else if (a == 2) {
      Dump(1, b);
    } else if (a == 3) {
      Dump(200, b - 2);
    } else if (a == 4) {
      Dump(20, b - 1);
    } else if (a == 5) {
      Dump(2, b);
    } else if (a == 6) {
      Dump(6, b);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
5 5
*/