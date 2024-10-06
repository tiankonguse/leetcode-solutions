/*
ID: tiankonguse
TASK: apple
LANG: C++
CONTEST: CSP-J 2023
OJ: https://qoj.ac/contest/1427/problem/7809
*/
#define TASK "apple"

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
题目：问几天苹果可以拿完，最后一个苹果是第几天拿走的。
思路：每天拿走 1/3 个苹果， `log(n)`天拿完。

1: 1(*)
2: 1 1(*)
3: 1 1 1(*)
4: 2(*) 1 1
*/
void Solver() {  //
  ll n;
  scanf("%lld", &n);

  ll all_day = 0, n_day = 0;
  while (n) {
    all_day++;
    ll choice = 1 + (n - 1) / 3;
    if (n_day == 0 && n % 3 == 1) {
      n_day = all_day;
    }
    n -= choice;
  }

  printf("%lld %lld\n", all_day, n_day);
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