/*
ID: tiankonguse
TASK: P1003 [NOIP2011 提高组] 铺地毯
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1003
PATH: noip2011 提高组 day1 第 1 题。
submission:
*/
#define TASK "1003"
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

int n;
vector<tuple<int, int, int, int>> nums;
void InitIO() {  //
                 // #ifdef USACO_LOCAL_JUDGE
                 //   freopen(TASK ".in", "r", stdin);
                 //   freopen(TASK ".out", "w", stdout);
                 // #endif
  scanf("%d", &n);
  nums.reserve(n);
  for (int i = 0; i < n; i++) {
    int a, b, g, k;
    scanf("%d%d%d%d", &a, &b, &g, &k);
    nums.push_back({a, b, a + g - 1, b + k - 1});
  }
}

void Solver() {  //
  int x, y;
  int ans = -1;
  scanf("%d%d", &x, &y);
  for (int i = n - 1; i >= 0; i--) {
    auto [x0, y0, x1, y1] = nums[i];
    if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
      ans = i + 1;
      break;
    }
  }
  printf("%d\n", ans);
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
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/