/*
ID: tiankonguse
TASK: decode
LANG: C++
https://www.luogu.com.cn/problem/P8814
*/
#define TASK "decode"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
constexpr int INF = 1 << 30;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

using int128 = __int128;

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

ll n, d, e;
ll q, p;
bool Check() {
  const int128 m = n - e * d + 2;
  if (m < 2) return false;  // 无解
  // 最大值 k = m/2
  int128 l = 1, r = m / 2;
  while (l < r) {
    int128 mid = (l + r) / 2;
    int128 Y = mid * (m - mid);
    if (n <= Y) {
      r = mid;
    } else if (n > Y) {
      l = mid + 1;
    }
  }
  if (r * (m - r) == n) {
    p = r;
    q = m - p;
    return true;
  }
  return false;
}
void Solver() {  //
  int k;
  scanf("%d", &k);
  while (k--) {
    scanf("%lld%lld%lld", &n, &d, &e);
    if (!Check()) {
      printf("NO\n");
    } else {
      printf("%lld %lld\n", p, q);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
