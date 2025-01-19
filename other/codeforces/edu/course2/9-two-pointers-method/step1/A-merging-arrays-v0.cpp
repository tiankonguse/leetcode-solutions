/*
ID: tiankonguse
TASK: A. Merging Arrays  A. 合并数组
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/A
PATH: ITMO Academy: pilot course » Two Pointers Method » Step 1 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "A-merging-arrays"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int n, m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
}

vector<ll> A, B, C;
void Solver() {  //
  A.reserve(n + 1);
  B.reserve(m + 1);
  C.reserve(n + m + 1);
  for (int i = 0; i < n; i++) {
    ll v;
    scanf("%lld", &v);
    A.push_back(v);
  }
  for (int i = 0; i < m; i++) {
    ll v;
    scanf("%lld", &v);
    B.push_back(v);
  }
  A.push_back(INT_MAX);
  B.push_back(INT_MAX);
  int a = 0, b = 0;
  while (a <= n && b <= m) {
    if (A[a] < B[b]) {
      C.push_back(A[a]);
      a++;
    } else {
      C.push_back(B[b]);
      b++;
    }
  }
  for (int i = 0; i < n + m; i++) {
    printf("%lld%c", C[i], i + 1 == n + m ? '\n' : ' ');
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