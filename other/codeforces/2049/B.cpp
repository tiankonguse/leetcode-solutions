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

int t;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
}

char str[555];

// <-P  S->
// sp : ok
// ps : err
bool Solver(int n) {
  int s = 0, p = 0;
  for (int i = 0; i < n; i++) {
    if (str[i] == 's') {
      s++;
      if (p) return false;
    } else if (str[i] == 'p') {
      p++;
    }
  }
  if (s == 0 || p == 0) return true;
  if (s > 1 && p > 1) return false;
  
  // 至少有一个字符是 1 个
  if (p == 1 && str[n - 1] == 'p') return true;
  if (s == 1 && str[0] == 's') return true;
  return false;
}

void Solver() {  //
  while (t--) {
    int n;
    scanf("%d", &n);
    scanf("%s", str);
    printf("%s\n", Solver(n) ? "YES" : "NO");
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