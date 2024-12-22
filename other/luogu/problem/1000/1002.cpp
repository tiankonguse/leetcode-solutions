/*
ID: tiankonguse
TASK: P1002 [NOIP2002 普及组] 过河卒
LANG: C++
MAC EOF: ctrl+D
link:
PATH: NOIP 2002 普及组第四题
submission:
*/
#define TASK "1002"
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

int n, m, x, y;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d%d%d", &n, &m, &x, &y);
}

ll nums[25][25];
ll flag[25][25];
int dir8[9][2] = {{0, 0},  {-1, -2}, {-2, -1}, {1, -2}, {2, -1},
                  {-1, 2}, {-2, 1},  {1, 2},   {2, 1}};

ll SolverEx() {
  memset(nums, 0, sizeof(nums));
  memset(flag, 0, sizeof(flag));
  for (int i = 0; i < 9; i++) {
    const int X = x + dir8[i][0];
    const int Y = y + dir8[i][1];
    if (X < 0 || X > n || Y < 0 || Y > m) continue;
    flag[X][Y] = 1;
  }

  nums[n + 1][m] = 1;
  for (int i = n; i >= 0; i--) {
    for (int j = m; j >= 0; j--) {
      if (flag[i][j]) continue;
      nums[i][j] = nums[i + 1][j] + nums[i][j + 1];
      // printf("i=%d j=%d ans=%lld\n", i, j, nums[i][j]);
    }
  }
  return nums[0][0];
}
void Solver() {  //
  printf("%lld\n", SolverEx());
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