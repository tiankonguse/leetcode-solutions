/*
ID: tiankonguse
TASK: E. 奇怪的运算
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/E
PATH:  ITMO 学院：试点课程”Z-函数”第 4 步”实践”
submission: https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/submission/297335979
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

const int N = 1e5 + 10;
char S[N];
char T[N];
int Z_ST[N];
int Z_TS[N];
void InitIO() {  //
  scanf("%s%s", S, T);
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

bool isSame(int n) {
  for (int i = 0; i < n; i++) {
    if (S[i] != T[i]) return false;
  }
  return true;
}

int ans = -1;
int Solver(const int n, const int m) {  //
  if (n != m) return ans = -1;

  if (isSame(n)) {
    return ans = 0;
  }

  int sn = n, tn = n;
  S[sn++] = T[tn++] = '$';
  for (int i = 0; i < n; i++) {
    S[sn++] = T[n - 1 - i];
    T[tn++] = S[i];
  }
  S[sn] = T[tn] = '\0';

  z_function(S, sn, Z_ST);
  z_function(T, tn, Z_TS);

  // S$-T: a0...an b0...bn $ a0...an bn...b0
  // T$+S: b0...bn an...a0 $ a0...an b0...bn
  for (int i = 1; i < n; i++) {  // 至少1个
    const int l = i, r = n - i;
    if (Z_ST[n + 1] >= l && Z_TS[tn - r] == r) {
      return ans = i;
    }
  }

  return ans = -1;
}
void Solver() {  //
  Solver(strlen(S), strlen(T));
  if (ans == -1) {
    printf("No\n");
  } else {
    printf("Yes\n%d\n", ans);
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