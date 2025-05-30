/*
ID: tiankonguse
TASK: checker
LANG: C++
MAC EOF: ctrl+D
HINT: Checker problem: Hint 4
DESC: SYMMETRY. Can you eliminate half or 3/4 of the cases you test by studying
rotations, reflections, or something like that? [hint: yes]
*/
#define TASK "checker"
#define TASKEX "-v14-v3"

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
void Dfs(int p) {  // 枚举第 p 行
  if (p == N + 1) {
    if (ans < 3) {
      top3.push_back(buf);
    }
    ans++;
    return;
  }
  for (int i = 1; i <= N; i++) {
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
    Dfs(p + 1);
    if (ans == 3) return;
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
vector<int> randRows;
vector<int> line1;
int Dfs1(int p, int L, int R) {  // 枚举第 p 行
  if (p == N + 1) {
    return 1;
  }
  int ret = 0;
  const int row = randRows[p];
  for (int i = L; i <= R; i++) {
    if (cols[i]) continue;
    if (g[row][i]) continue;
    auto [x0, y0] = Trans0(row, i);
    auto [x1, y1] = Trans1(row, i);
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
    int tmp = Dfs1(p + 1, l, r);
    ret += tmp;
    if (p == 1) {
      line1[i] = tmp;
      if (i >= (N + 1) / 2) {
        for (int l = 1, r = N; l < r; l++, r--) {
          line1[r] = line1[l];
          ret += line1[l];
        }
        break;
      }
    }
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
  return ret;
}

void Init() {
  memset(g, 0, sizeof(g));
  memset(cols, 0, sizeof(cols));
  memset(LU_RD, 0, sizeof(LU_RD));
  memset(RU_LD, 0, sizeof(RU_LD));
  line1.resize(N + 1, 0);

  randRows.clear();
  randRows.push_back(0);
  for (int i = N / 2, j = N / 2 + 1; i >= 1 || j <= N; i--, j++) {
    if (i >= 1) randRows.push_back(i);
    if (j <= N) randRows.push_back(j);
  }
}
void SolverInput() {  //
  scanf("%d", &N);
}

void Solver() {  //
  Init();
  // 由于对称性，第一行只需要枚举一半
  Dfs(1);
  Init();
  ans = Dfs1(1, 1, N);
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
   Test 1: TEST OK [0.000 secs limit:1s, 1784 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1632 KB]
   Test 3: TEST OK [0.007 secs limit:1s, 1636 KB]
   Test 4: TEST OK [0.007 secs limit:1s, 1712 KB]
   Test 5: TEST OK [0.007 secs limit:1s, 1692 KB]
   Test 6: TEST OK [0.042 secs limit:1s, 1696 KB]
   Test 7: TEST OK [0.196 secs limit:1s, 1740 KB]
   Test 8: TEST OK [0.970 secs limit:1s, 1740 KB]

All tests OK.
Your program ('checker') produced all correct answers!  This is your
submission #12 for this problem.  Congratulations!

Here are the test data inputs:

------- test 1 [length 2 bytes] ----
6
------- test 2 [length 2 bytes] ----
7
------- test 3 [length 2 bytes] ----
8
------- test 4 [length 2 bytes] ----
9
------- test 5 [length 3 bytes] ----
10
------- test 6 [length 3 bytes] ----
11
------- test 7 [length 3 bytes] ----
12
------- test 8 [length 3 bytes] ----
13
Keep up the good work!
*/