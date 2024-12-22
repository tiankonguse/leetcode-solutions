/*
ID: tiankonguse
TASK: T417326 分饼干 I
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/T417326?contestId=151796
PATH: 【LGR-172-Div.4】洛谷入门赛 #19
submission:
*/
#define TASK "A"
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

const int n = 3;
ll sum = 0;
int nums[5];
void InitIO() {  //
// #ifdef USACO_LOCAL_JUDGE
//   freopen(TASK ".in", "r", stdin);
//   freopen(TASK ".out", "w", stdout);
// #endif
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
    sum += nums[i];
  }
}

int x, y;
void Update(int a, int b) {
  if (a < b) return;
  if (x - y > a - b) {
    x = a;
    y = b;
  }
}
void Solver() {  //
  x = sum;
  y = 0;
  for (int i = 0; i < n; i++) {
    int v = nums[i];
    Update(v, sum - v);
    Update(sum - v, v);
  }
  printf("%d %d\n", x, y);
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