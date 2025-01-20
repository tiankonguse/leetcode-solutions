/*
ID: tiankonguse
TASK: A. Packing Rectangles  A. 包装矩形
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/A
PATH: ITMO Academy: pilot course » Binary Search » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "A-packing-rectangles"
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

ll w, h, n;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld%lld", &w, &h, &n);
}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 61

bool Check(ll m) {
  ll a = m / w;
  ll b = m / h;
  return (n + a - 1) / a <= b;
}

ll Search() {
  ll l = max(w, h), r = max(w, h) * n + 1;
  while (l < r) {  // [l,r)
    ll m = (l + r) / 2;
    if (Check(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return r;
}
void Solver() {  //
  // printf("%s\n", to_string(Search()).data());
  printf("%lld\n", Search());
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