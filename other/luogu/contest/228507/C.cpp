/*
ID: tiankonguse
TASK: Standard Problem.
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "C"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 3000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int t;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
}
// ll qpow(ll x, ll v, ll mod) {
//   x = x % mod;
//   ll y = 1;
//   while (v) {
//     if (v & 1) y = y * x % mod;
//     x = x * x % mod;
//     v >>= 1;
//   }
//   return y;
// }
// ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }
ull n, k;
char str[max6];

// ull C2(ull n) { return n * (n - 1) % mod * inv(2, mod) % mod; }
void Solver() {  //
  while (t--) {
    scanf("%llu%llu%s", &n, &k, str);
    if (n == 1) {
      k = k % mod;
      printf("%llu\n", (k + 1) * k / 2 % mod);
    } else if (n == 2) {
      if (str[0] == str[1]) {
        k = k % mod;
        printf("%llu\n", (2 * k + 1) % mod * k % mod);
      } else {
        printf("%llu\n", k * (k + 1) % mod);
      }
    } else {
      printf("0\n");
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
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/