/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "C-v3"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef __int128_t int128;

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

const ll mod = 2933256077ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

const int N = 6e6 + 10;
int n, m;
char str[N];
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d%s", &n, &m, str);
}

inline ll mul(ll a, ll b) { return a * b % mod; }

ll qpow(ll x, ll v) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = mul(y, x);
    x = mul(x, x);
    v >>= 1;
  }
  return y;
}
ll inv(ll x, ll mod) { return qpow(x, mod - 2); }

/*
A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

ll A[N + 1];
ll RA[N + 1];
// vector<ll> A;
// vector<ll> RA;

void InitA(int n) {
  // A.resize(n + 1);
  A[0] = 1;

  for (int i = 1; i <= n; i++) {
    A[i] = (A[i - 1] * i) % mod;
  }

  // RA.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    RA[i] = inv(A[i], mod);
  }
}

inline ll C(ll n, ll r) {
  ll Anr = mul(A[n], RA[n - r]);
  return mul(Anr, RA[r]);
}
inline ll Cal(ll preOneNum, ll leftZeroNum) {  //  0 都插入到 1 前面
  if (preOneNum == 0 && leftZeroNum == 0) return 1;
  if (leftZeroNum == 0) return 1;
  if (preOneNum == 0) return 0;
  return C(leftZeroNum + preOneNum - 1, preOneNum - 1);
}

ll ans = 0;
void Solver() {  //
  ll nm[2] = {0, 0};
  const ll NM[2] = {m, n};
  InitA(n + m + 1);
  for (int i = 0; i < n + m; i++) {
    // printf("mi=%lld ni=%lld\n", nm[0], nm[1]);
    const int v0 = str[i] - '0';  // 当前值是 v0 ，使用 v1 堵住
    const int v1 = 1 - v0;
    // if (i > 0 && nm[v1] < NM[v1] && nm[v0] <= NM[v0]) {
    if (i > 0) {
      ll preV0 = nm[v0];
      ll preV1 = nm[v1];
      ll leftV0 = NM[v0] - preV0;
      ll leftV1 = NM[v1] - preV1;  // 独占消耗一个
      // if (nm[v0] == NM[v0]) {          // 已经用完了，不需要单独消耗一个
      //   leftV1++;
      // }
      ll numi = mul(Cal(preV1, leftV0), Cal(preV0 + 1, leftV1));
      ll ansi = (numi * i) % mod;
      // printf("preV1=%lld leftV0=%lld C=%lld\n", preV1, leftV0, ll(Cal(preV1, leftV0)));
      // printf("preV0+1=%lld leftV1=%lld C=%lld\n", preV0 + 1, leftV1, ll(Cal(preV0 + 1, leftV1)));
      ans = (ans + ansi) % mod;
      // printf("i=%d numi=%lld ansi=%lld ans=%lld\n", i, ll(numi), ll(ansi), ll(ans));
    }
    if (nm[v0] < NM[v0]) {
      nm[v0]++;
    } else {
      break;
    }
  }
  if (nm[1] == n && nm[0] == m) {
    ans = (ans + n + m) % mod;
  }
  printf("%lld\n", ans);
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
5 5
0010111011
3: 1111000001
3: 1110100001
3: 1110000011
3: 1101100001
3: 1101000011
3: 1100000111
3: 1011100001
3: 1011000011
3: 1010000111
3: 1000001111
3: 0111100001
3: 0111000011
3: 0110000111
3: 0100001111
3: 0000011111
len=0 num=0 ans=0
len=1 num=0 ans=0
len=2 num=6 ans=12
len=3 num=15 ans=45
len=4 num=45 ans=180
len=5 num=60 ans=300
len=6 num=60 ans=360
len=7 num=40 ans=280
len=8 num=20 ans=160
len=9 num=6 ans=54
len=10 num=0 ans=0
1391
*/