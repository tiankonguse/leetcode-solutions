/*
ID: tiankonguse
TASK: B Swap & Delete
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/contest/210959
PATH:【LGR-210-Div.3】洛谷基础赛 #19 & ALFR Round 3
submission:
*/
#define TASK "B"
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

int t;
void InitIO() {  //
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d", &t);
}

int n;
unordered_map<int, int> h;
const int N = 1e5 + 10;
int nums[N];
int two = 0;
int solverEx() {
  if (nums[0] == nums[n - 1]) return 1;
  if (h[nums[0]] > 1 || h[nums[n - 1]] > 1) return 2;
  if (two) return 3;
  return n;
}

void Solver() {  //
  while (t--) {
    scanf("%d", &n);
    h.clear();
    two = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &nums[i]);
      h[nums[i]]++;
      if (h[nums[i]] > 1) {
        two = 1;
      }
    }
    printf("%d\n", solverEx());
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
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/