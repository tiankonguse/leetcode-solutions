/*
ID: tiankonguse
TASK: checker
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "checker"
#define TASKEX "-v4"

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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int g[15][15];
int cols[15];
int LU_RD[15][15];
int RU_LD[15][15];
vector<int> buf;
int N;

inline pair<int, int> Trans0(int x, int y) {
  int v = min(x - 1, y - 1);
  return {x - v, y - v};
}
inline pair<int, int> Trans1(int x, int y) {
  int v = min(x - 1, N - y);
  return {x - v, y + v};
}

int ans = 0;
vector<vector<int>> top3;
void Dfs(int p, int L, int R) {  // 枚举第 p 行
  if (p == N + 1) {
    if (ans < 3) {
      top3.push_back(buf);
    }
    ans++;
    return;
  }
  for (int i = L; i <= R; i++) {
    if (cols[i]) continue;
    if (g[p][i]) continue;
    auto [x0, y0] = Trans0(p, i);
    auto [x1, y1] = Trans1(p, i);
    if (LU_RD[x0][y0]) continue;
    if (RU_LD[x1][y1]) continue;

    cols[i]++;
    LU_RD[x0][y0]++;
    RU_LD[x1][y1]++;
    buf.push_back(i);
    for (int x = x0, y = y0; x <= N && y <= N; x++, y++) {
      g[x][y]++;
    }
    for (int x = x1, y = y1; x <= N && y >= 1; x++, y--) {
      g[x][y]++;
    }
    int l = L, r = R;
    while (l <= r && cols[l]) {
      l++;
    }
    while (l <= r && cols[r]) {
      r--;
    }
    Dfs(p + 1, l, r);
    for (int x = x0, y = y0; x <= N && y <= N; x++, y++) {
      g[x][y]--;
    }
    for (int x = x1, y = y1; x <= N && y >= 1; x++, y--) {
      g[x][y]--;
    }

    cols[i]--;
    LU_RD[x0][y0]--;
    RU_LD[x1][y1]--;
    buf.pop_back();
  }
}

void Init() {
  memset(g, 0, sizeof(g));
  memset(cols, 0, sizeof(cols));
  memset(LU_RD, 0, sizeof(LU_RD));
  memset(RU_LD, 0, sizeof(RU_LD));
  //   for (int i = 1; i <= N; i++) {
  //     for (int j = 1; j <= N; j++) {
  //       auto [x0, y0] = Trans0(i, j);
  //       auto [x1, y1] = Trans1(i, j);
  //       printf("(%d,%d) left-top:(%d,%d) right-top:(%d,%d)\n", i, j, x0, y0,
  //       x1,
  //              y1);
  //     }
  //   }
}
void SolverInput() {  //
  scanf("%d", &N);
}

void Solver() {  //
  Init();
  Dfs(1, 1, N);
  for (auto& vs : top3) {
    for (int i = 0; i < N; i++) {
      printf("%d%c", vs[i], i + 1 == N ? '\n' : ' ');
    }
  }
  printf("%d\n", ans);
}

void ExSolver() {
  SolverInput();
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
Executing...
   Test 1: TEST OK [0.004 secs limit:1s, 1636 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1636 KB]
   Test 3: TEST OK [0.004 secs limit:1s, 1632 KB]
   Test 4: TEST OK [0.007 secs limit:1s, 1632 KB]
   Test 5: TEST OK [0.018 secs limit:1s, 1688 KB]
   Test 6: TEST OK [0.067 secs limit:1s, 1720 KB]
   Test 7: TEST OK [0.343 secs limit:1s, 1688 KB]
  > Run 8: Execution error: Your program (`checker') used more than
        the allotted runtime of 1 seconds (it ended or was stopped at
        1.855 seconds) when presented with test case 8. It used 1704 KB of
        memory. 

        ------ Data for Run 8 [length=3 bytes] ------
        13 
        ----------------------------
    Test 8: RUNTIME 1.855>1 (1704 KB)

13
1 3 5 2 9 12 10 13 4 6 8 11 7
1 3 5 7 9 11 13 2 4 6 8 10 12
1 3 5 7 12 10 13 6 4 2 8 11 9
73712
my 用时: 748ms
*/