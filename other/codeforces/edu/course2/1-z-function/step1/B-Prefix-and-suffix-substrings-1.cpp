/*
ID: tiankonguse
TASK: B. 前缀和后缀子串 - 1
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/B
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤1 » 实践
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

int q;
void InitIO() {  //
  scanf("%d", &q);
}

const int N = 550;
char str[N];
int Z[N * 2 + 10];

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

int isPrefixAndSuffix[N];  // [0,n)
int preSum[N];             // [1,n]

int Solver(int n, int nn) {
  z_function(str, nn, Z);
  for (int i = 0; i <= n; i++) {
    isPrefixAndSuffix[i] = 0;
    preSum[i] = 0;
  }
  for (int i = n + 1; i < nn; i++) {
    if (i + Z[i] == nn) {
      isPrefixAndSuffix[Z[i] - 1] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    preSum[i + 1] = preSum[i] + isPrefixAndSuffix[i];
  }

  int ans = 0;

  Z[0] = n;
  for (int i = 0; i < n; i++) {
    ans += Z[i] - preSum[Z[i]];
  }
  return ans;
}

int Solver(const int n) {
  str[n] = '$';
  for (int i = 0, j = n + 1; i < n; i++, j++) {
    str[j] = str[i];
    isPrefixAndSuffix[i] = 0;
  }
  int nn = 2 * n + 1;
  str[nn] = '\0';

  int ans = Solver(n, nn);

  for (int l = 0, r = nn - 1; l < r; l++, r--) {
    swap(str[l], str[r]);
  }

  ans += Solver(n, nn);

  return ans;
}

void Solver() {  //
  getchar();     // skip \n
  while (q--) {
    fgets(str, N, stdin);
    int n = strlen(str);  // skip \n
    str[--n] = '\0';
    // printf("str[%s] n[%d]\n", str, n);
    printf("%d\n", Solver(n));
  }
}
// str[barbarmiakirkudu] n[16]

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