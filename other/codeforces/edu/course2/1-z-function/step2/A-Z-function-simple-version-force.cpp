/*
ID: tiankonguse
TASK: A. Z-函数（简单版本）
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/problem/A
PATH: ITMO 学院：试点课程”Z-函数”第 2 步”实践”
submission:
https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/submission/297237496
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

const int S = 3300;
char str[S];
int Z[S];
void InitIO() {  //
  scanf("%s", str);
}

void z_function(char* s, const int n, int* z) {  //
  z[0] = 0;
  for (int i = 1; i < n; i++) {
    Z[i] = 0;
    for (int j = 0; i + j < n && s[j] == s[i + j]; j++) {
      Z[i] = j + 1;
    }
  }
}

void Solver() {  //
  int n = strlen(str);
  z_function(str, n, Z);
  for (int i = 0; i < n; i++) {
    printf("%d%c", Z[i], i + 1 == n ? '\n' : ' ');
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