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

const int N = 2e5 + 10;
int nums[N];

int Mex(int a, int b, int c) {
  vector<int> bits(5, 0);
  bits[a] = bits[b] = bits[c] = 1;
  set<int> s = {a, b, c};
  for (int i = 0;; i++) {
    if (bits[i] == 0) return i;
  }
  return 0;
}
void Solver(int n, int x, int y) {
  nums[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (i == y) {
      if (i == n) {
        int a = nums[i - 1];
        int b = nums[x];
        int c = nums[1];
        nums[i] = Mex(a, b, c);
      } else {
        int a = nums[i - 1];
        int b = nums[x];
        nums[i] = Mex(a, b, a);
      }
    } else {
      if (i == n) {
        int a = nums[i - 1];
        int b = nums[1];
        nums[i] = Mex(a, b, a);
      } else {
        int a = nums[i - 1];
        nums[i] = Mex(a, a, a);
      }
    }
  }
}

void Solver() {  //
  while (t--) {
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    Solver(n, x, y);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", nums[i], i == n ? '\n' : ' ');
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