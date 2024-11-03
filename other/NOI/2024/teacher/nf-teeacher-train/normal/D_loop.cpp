/*
ID: tiankonguse
TASK: D
LANG: C++
*/
#define TASK "D"

#include <bits/stdc++.h>

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

using namespace std;
typedef long long ll;

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<ll> A;
vector<ll> B;

ll BinarySearch(const ll R) {  // 只能查找 R
  ll l = 1, r = A[n - 1] + B[n - 1] + 1;
  while (l < r) {
    ll mid = (l + r) / 2;
    ll numAll = 0;
    for (int a = 0; a < n; a++) {  // 找 <= mid 的个数
      const ll av = A[a];
      const ll bv = mid - av;
      const ll num = upper_bound(B.begin(), B.end(), bv) - B.begin();
      numAll += num;
    }
    if (numAll < R) {  // 不够
      l = mid + 1;
    } else if (numAll >= R) {  // 恰好找到 L 个, mid 处于空洞里时也满足
      r = mid;
    }
  }
  // printf("BinarySearch R=%lld RV=%lld\n", R, l);
  return l;
}

void Solver() {  //
  ll L, R;
  scanf("%lld%lld%lld", &n, &L, &R);
  A.resize(n);
  B.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%lld", &B[i]);
  }
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  for (ll i = L; i <= R; i++) {
    printf("%lld%c", BinarySearch(i), i == R ? '\n' : ' ');
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
12
1 1 3 3 5 5 6 6 8 8 9 9
2 2 3 3 4 4 5 5 6 6 7 7
*/
