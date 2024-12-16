/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

void InitIO() {  //
}

/*
A  :
B  :
AB :AB(i) = B(A(i))

A + B = B(A(i))

y = AB(0) = B(A(0)) = B(a0)
y1 = B(a1)
y2 = B(a2)

ans = 1 * B(1) + 2 * B(2)

B =




*/

int n, m;
int t, q;
vector<ll> nums;
vector<ll> preSums;
vector<ll> preAns;

inline ll FastReadNum() {
  char c = getchar();
  while (!(c >= '0' && c <= '9')) {  // skip blank
    c = getchar();
  }

  ll v = 0;
  while (c >= '0' && c <= '9') {
    v = v * 10 + (c - '0');
    c = getchar();
  }
  return v;
}

void Solver() {  //
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    nums.resize(m + 1, 0);
    preSums.resize((n + 1) * (m + 1), 0);
    preAns.resize(n + 1, 0);

    preAns[0] = 0;
    for (int j = 1; j <= m; j++) {
      preSums[j] = j;
      preAns[0] += j * j;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        nums[j] = FastReadNum();
      }
      ll* p = &(preSums[0]);
      auto A = p + (i - 1) * (m + 1);
      auto& B = nums;
      auto AB = p + (i) * (m + 1);
      preAns[i] = 0;
      for (int j = 1; j <= m; j++) {
        AB[j] = B[A[j]];  // AB(j) = B(A(j))
        preAns[i] += j * AB[j];
      }
    }
    scanf("%d", &q);
    ll* p = &(preSums[0]);
    while (q--) {
      int l, r;
      l = FastReadNum();
      r = FastReadNum();
      ll ans = 0;  // sum(i * B[i])
      auto A = p + (l - 1) * (m + 1);
      auto AB = p + (r) * (m + 1);
      for (int j = 1; j <= m; j++) {  // AB(j) = B(A(j))
        int i = A[j];
        ans += i * AB[j];
      }
      printf("%lld\n", ans);
    }
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  InitIO();
  ExSolver();
  return 0;
}

/*

*/