/*
ID: tiankonguse
TASK: chessboard
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "chessboard"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
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
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 2
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

// 判断一个数是否为质数
// 时间复杂度 O(sqrt(n))
bool IsPrime2(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return n >= 2;  // 1 不是质数, 2和3是质数
}

vector<int> isPrm;
vector<set<int>> edges;
vector<pair<int, int>> orders;  // 枚举顺序
int nn;
int maxAns = 0;
int maxOffsetVal = 0;  // 第一行与第一列允许的最大值
void Init(int n) {
  isPrm.resize(300, 0);
  for (int i = 2; i < 300; i++) {
    if (IsPrime2(i)) {
      isPrm[i] = 1;
    }
  }
  nn = n * n;
  edges.resize(nn + 1);
  for (int i = 1; i <= nn; i++) {
    // MyPrintf("%d: ", i);
    for (int j = nn; j >= 1; j--) {
      if (i == j) continue;
      if (isPrm[i + j]) {
        edges[i].insert(j);
        // MyPrintf("%d ", j);
      }
    }
    // MyPrintf("\n");
  }

  orders.reserve(nn);
  for (int k = 0; k < n; k++) {
    orders.push_back({k, k});
    for (int i = k + 1; i < n; i++) {
      orders.push_back({k, i});
      orders.push_back({i, k});
    }
  }
}

vector<vector<int>> g;
vector<vector<int>> ans;
vector<int> flag;
int ansSum = 0;
int n;
void UpdateAns() {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += g[i][0];
    sum += g[0][i];
  }
  sum -= g[0][0];
  if (sum < ansSum) {
    ans = g;
    ansSum = sum;
  }
}
void Dfs(const int offset, const int sum) {
  if (ansSum == maxAns) return;  // 已经找到最优解
  const auto [x, y] = orders[offset];
  if (offset == nn) {
    UpdateAns();
    return;
  }
  if (offset < 2 * n - 1 && sum > maxAns) {
    return;  // 第一行和第一列都填充完了，剪枝判断
  }
  if (offset == 2 * n - 1 && sum != maxAns) {
    return;  // 第一行和第一列都填充完了，剪枝判断
  }
  // 根据已填充的相邻位置的值，枚举当前位置可能的值
  int preVal = x > 0 ? g[x - 1][y] : g[x][y - 1];
  for (const auto val : edges[preVal]) {
    if (flag[val]) continue;                                 // 已经使用过
    if (x > 0 && !isPrm[g[x - 1][y] + val]) continue;        // 上个位置和当前位置不相邻
    if (y > 0 && !isPrm[g[x][y - 1] + val]) continue;        // 左个位置和当前位置不相邻
    if (offset < 2 * n - 1 && val > maxOffsetVal) continue;  // 第一行与第一列的值不能过大
    g[x][y] = val;
    flag[val] = 1;
    Dfs(offset + 1, sum + val);
    flag[val] = 0;
  }
}

void Solver2() {
  // try maxOffsetVal=3 maxAns=6
  // try maxOffsetVal=4 maxAns=9
  printf("1 2\n");
  printf("4 3\n");
  // my 用时: 866ms
}
void Solver4() {  //
  printf("1 2 11 12\n");
  printf("4 9 8 5\n");
  printf("7 10 3 14\n");
  printf("6 13 16 15\n");
  // try maxOffsetVal=7 maxAns=28
  // try maxOffsetVal=8 maxAns=35
  // try maxOffsetVal=9 maxAns=42
  // try maxOffsetVal=10 maxAns=49
  // try maxOffsetVal=11 maxAns=56
  // try maxOffsetVal=12 maxAns=63
  // my 用时: 1788ms
}
void Solver5() {
  printf("1 2 3 4 13\n");
  printf("6 5 14 15 16\n");
  printf("7 24 23 8 21\n");
  printf("10 19 18 11 20\n");
  printf("9 22 25 12 17\n");
  // try maxOffsetVal=9 maxAns=45
  // try maxOffsetVal=10 maxAns=54
  // try maxOffsetVal=11 maxAns=63
  // try maxOffsetVal=12 maxAns=72
  // try maxOffsetVal=13 maxAns=81
  // my 用时: 1490ms
}
void Solver6() {  //
  printf("1 2 3 8 9 4\n");
  printf("6 11 20 33 28 25\n");
  printf("5 36 23 14 15 22\n");
  printf("12 31 30 17 26 21\n");
  printf("7 16 13 24 35 32\n");
  printf("10 27 34 19 18 29\n");
  // try maxOffsetVal=11 maxAns=66
  // try maxOffsetVal=12 maxAns=77
  // my 用时: 13200ms
}
void Solver7() {
  printf("1 2 3 8 5 12 11\n");
  printf("4 15 14 23 18 49 30\n");
  printf("7 16 45 38 41 48 31\n");
  printf("6 25 22 21 32 35 36\n");
  printf("13 34 39 20 47 24 37\n");
  printf("10 19 40 33 26 17 42\n");
  printf("9 28 43 46 27 44 29\n");
  // try maxOffsetVal=13 maxAns=91
  // my 用时: 1166ms
}
void Solver8() {
  printf("1 2 3 8 9 10 13 16\n");
  printf("4 15 26 21 20 27 34 37\n");
  printf("7 22 45 52 51 46 55 42\n");
  printf("6 25 58 31 28 61 48 59\n");
  printf("11 18 49 30 43 36 23 38\n");
  printf("12 19 54 29 60 53 44 63\n");
  printf("5 24 35 32 47 50 39 64\n");
  printf("14 17 62 41 56 57 40 33\n");
  // try maxOffsetVal=15 maxAns=120
  // try maxOffsetVal=15 maxAns=121
  // my 用时: 1628ms
}
void Solver9() {
  printf("1 2 3 8 9 10 13 16 15\n");
  printf("4 27 20 21 22 19 24 37 46\n");
  printf("7 34 33 26 45 52 49 60 67\n");
  printf("6 25 28 81 58 55 54 47 42\n");
  printf("5 18 43 70 79 48 53 56 71\n");
  printf("14 23 36 61 78 59 50 57 80\n");
  printf("17 30 31 66 35 68 63 74 77\n");
  printf("12 29 72 65 44 39 64 75 62\n");
  printf("11 32 41 38 69 40 73 76 51\n");
  // try maxOffsetVal=17 maxAns=153
  // my 用时: 6223ms
}
void Solver10() {
  // try maxOffsetVal=19 maxAns=190
  // try maxOffsetVal=19 maxAns=191
  printf("1 2 3 8 5 12 17 14 15 16\n");
  printf("4 27 26 21 32 29 24 47 56 45\n");
  printf("7 34 33 38 35 44 59 42 41 62\n");
  printf("6 25 28 69 68 63 50 89 48 65\n");
  printf("11 36 43 58 99 74 53 84 83 66\n");
  printf("18 23 60 49 64 75 98 95 54 97\n");
  printf("13 30 37 90 67 82 81 86 77 96\n");
  printf("10 31 52 61 46 55 76 51 80 71\n");
  printf("9 22 19 78 85 72 91 100 57 92\n");
  printf("20 39 40 73 94 79 88 93 70 87\n");
  // my 用时: 22798ms
}
void Solver11() {
  printf("1 2 3 8 5 12 17 20 9 14 15\n");
  printf("4 27 26 33 38 29 24 47 32 39 28\n");
  printf("7 34 45 56 41 60 49 54 35 44 69\n");
  printf("6 25 58 51 62 77 90 59 48 65 98\n");
  printf("11 36 43 88 75 74 83 80 119 92 101\n");
  printf("18 23 66 85 52 57 116 113 110 89 50\n");
  printf("13 30 71 96 97 40 111 68 63 104 107\n");
  printf("16 31 78 53 114 67 100 99 64 93 86\n");
  printf("21 22 61 120 79 70 81 112 87 106 105\n");
  printf("10 37 46 91 102 109 82 117 94 73 118\n");
  printf("19 42 55 72 95 84 115 76 103 108 121\n");
  // try maxOffsetVal=21 maxAns=231
  // my 用时: 62798ms
}
void Solver() {  //
  scanf("%d", &n);
  Init(n);
  ans.resize(n, vector<int>(n, n * n));
  ansSum = INT_MAX;
  g.resize(n, vector<int>(n));
  flag.resize(n * n + 1, 0);
  g[0][0] = 1;
  flag[1] = 1;
  if (n == 1 || n == 3) {
    printf("NO\n");
  } else if (n == 2) {
    Solver2();
  } else if (n == 4) {
    Solver4();
  } else if (n == 5) {
    Solver5();
  } else if (n == 6) {
    Solver6();
  } else if (n == 7) {
    Solver7();
  } else if (n == 8) {
    Solver8();
  } else if (n == 9) {
    Solver9();
  } else if (n == 10) {
    Solver10();
  } else if (n == 11) {
    Solver11();
  } else {
    maxAns = n * (2 * n - 1);
    maxOffsetVal = 2 * n - 1;
    int maxLoop = 10;
    while (ansSum == INT_MAX && maxLoop > 0) {
      MyPrintf("try maxOffsetVal=%d maxAns=%d\n", maxOffsetVal, maxAns);
      for (int i = maxAns - (2 * n - 1) * (n - 1); i >= 2 * n - 1 && ansSum == INT_MAX; i--) {
        maxOffsetVal = i;
        Dfs(1, 1);
      }
      maxAns++;
      maxLoop--;
    }

    if (ansSum < INT_MAX) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          printf("%d ", ans[i][j]);
        }
        printf("\n");
      }
    } else {
      printf("NO\n");
    }
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}

/*
N=2 用时: 866ms
N=4 用时: 1788ms
N=5 用时: 1490ms
N=6 用时: 13200ms
N=7 用时: 1166ms
N=8 用时: 1628ms
N=9 用时: 6223ms
N=10 用时: 22798ms
N=11 用时: 62798ms
*/

