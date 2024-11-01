/*
ID: tiankonguse
TASK: B
LANG: C++
*/
#define TASK "A"

#include <bits/stdc++.h>

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
}


// y^2=n+x^2
// 另 y=(x+k), n = y^2-x^2 = k^2+2kx, x = (n-k^2) / 2k
// n 为奇数，必须满足 n=2x+1, n>=3
// n 为偶数，必须满足 n=4x+4, n>=8, && n % 4 == 0
// 满足条件情况下，二分 k

ll Solver(ll n) {
  if (n % 2 == 1) {
    if (n < 3) return -1;
  } else {
    if (n % 4 != 0) return -1;
    if (n < 8) return -1;
  }

  //
  ll l = 1, r = sqrt(n);
  for (int k = r; k >= l; k--) {  // k 越大, x 越小
    if (k * k == n) continue;
    if ((n - k * k) % (2 * k) == 0) {
      return (n - k * k) / (2 * k);
    }
  }
  return -1;
}

void Solver() {  //
  ll n;
  scanf("%lld", &n);
  printf("%lld\n", Solver(n));
}

int main() {
  InitIO();
  Solver();
  return 0;
}
