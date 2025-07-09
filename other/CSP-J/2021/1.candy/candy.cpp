/*
ID: tiankonguse
TASK: candy
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P7909
PATH: P7909 [CSP-J 2021] 分糖果
submission:
*/
#define TASK "candy"
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

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
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

void InitIO(int fileIndex) {  //
#ifdef USACO_LOCAL_JUDGE
#define USACO_TASK_FILE 3
#define TASKNO 1
#ifndef USACO_TASK_FILE 
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
}

ll Solver(ll n, ll L, ll R) {  //
  if (L == R) {
    return L % n;
  }
  ll LR = R - L + 1;
  if (LR >= n) {  // 可选的数量大于等于n，可以得到任何余数，返回最大余数
    return n - 1;
  }

  ll ln = L % n;
  ll rn = R % n;
  if (ln <= rn) {  // 递增，说明余数递增
    return rn;
  } else {
    return n - 1;  // 否则，余数超过最大值后从0重新开始
  }
}

ll Solver2(ll n, ll L, ll R) {  //
  if (L / n < R / n) {          // 可选的数量大于等于n，可以得到任何余数，返回最大余数
    return n - 1;
  }
  return R % n;
}

void Solver() {  //
  ll n, L, R;
  scanf("%lld%lld%lld", &n, &L, &R);
  printf("%lld\n", Solver2(n, L, R));
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t1 = std::chrono::steady_clock::now();
#endif
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
  }
#endif
  return 0;
}

/*

*/