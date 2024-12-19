/*
ID: tiankonguse
TASK: D. 良好子字符串的数量 - 1
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/D
PATH: ITMO 学院：试点课程”Z-函数”第 1 步”实践”
submission: https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/submission/297236173
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

int q;
void InitIO() {  //
  scanf("%d", &q);
}

const int T = 111;
const int S = 50110 + T;
char str[S];
char pat[T];

int Z[S];

void z_function(char* s, const int n, int* z) {  //
  memset(z, 0, n * sizeof(z[0]));
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < n; i++) {
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

ll Solver(int n, int m) {
  for (int i = 0; i < m; i++) {
    str[i] = pat[i];
  }
  str[m] = '$';
  for (int i = m + 1, j = 0; j < n; i++, j++) {
    str[i] = str[T + j];
  }

  int nm1 = n + m + 1;
  str[nm1] = '\0';
  // printf("n+$+m=[%s]\n", str);

  z_function(str, nm1, Z);

  ll ans = 0;
  ll last = nm1;
  for (int i = nm1 - 1; i >= m + 1; i--) {
    if (Z[i] != m) {
      ans += last - i;  // 以 i 开始的所有好子串 [i, last)
    } else {
      ans += m - 1;
      last = i + m - 1;
    }
  }
  return ans;
}

void Solver() {  //
  while (q--) {
    scanf("%s%s", str + T, pat);
    int n = strlen(str + T);
    int m = strlen(pat);
    printf("%lld\n", Solver(n, m));
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