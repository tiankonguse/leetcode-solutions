/*
ID: tiankonguse
TASK: H. 不同子串的长度之和
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/H
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/submission/297455104
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

const int N = 1e4 + 10;
char S[N];
int Z[N];
void InitIO() {  //
  scanf("%s", S);
}

void z_function(char* s, int n, int* z) {  //
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < n; i++) {
    z[i] = 0;
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
}
void Solver() {  //
  ll ans = 0;
  int n = strlen(S);
  for (int i = n - 1; i >= 0; i--) {
    int nn = n - i;
    z_function(S + i, nn, Z);
    int maxPre = 0;
    for (int j = 0; j < nn; j++) {
      maxPre = max(maxPre, Z[j]);
    }
    ll l = maxPre, r = nn;  // (l, r]
    ans += (1 + r) * r / 2 - (1 + l) * l / 2;
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