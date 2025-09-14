/*
ID: tiankonguse
TASK: zoo
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7076
PATH:  P7076 [CSP-S2020] 动物园
submission:
*/
#define TASK "zoo"
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

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "3"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

string MyToString(__int128_t ans) {
  string str;
  while (ans > 0) {
    str.push_back(ans % 10 + '0');
    ans /= 10;
  }
  reverse(str.begin(), str.end());
  if (str.empty()) {
    return "0";
  } else {
    return str;
  }
}

void Solver() {  //
  ll n, m, c, k;
  scanf("%lld%lld%lld%lld", &n, &m, &c, &k);
  ull mask = 0;
  for (int i = 0; i < n; i++) {
    ull x;
    scanf("%llu", &x);
    mask |= x;
  }
  ull umask = 0;
  for (int i = 0; i < m; i++) {
    int p;
    ull q;
    scanf("%d%llu", &p, &q);
    if ((mask & (1ULL << p)) == 0) {
      umask |= (1ULL << p);
    }
  }
  int bit = 0;
  for (int i = 0; i < k; i++) {
    if (umask & (1ULL << i)) {
      bit++;
    }
  }
  __int128_t ans = 1;
  for (int i = 0; i < k - bit; i++) {
    ans *= 2;
  }
  ans -= n;
  string str = MyToString(ans);
  printf("%s\n", str.c_str());
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