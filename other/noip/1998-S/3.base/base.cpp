/*
ID: tiankonguse
TASK: base
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "base"
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

vector<vector<string>> table;
char str[5];
int n;

map<string, int> H;
map<int, string> h;
int B = 0;
bool Check() {
  B = n - 1;
  // 第一步：找到 0 对应的字符
  for (int i = 1; i < n; i++) {
    int towBit = 0;
    for (int j = 1; j < n; j++) {
      if (table[i][j].size() == 2) {
        towBit++;
      }
    }
    H[table[i][0]] = towBit;
    if (h.count(towBit)) {
      MyPrintf("h[%d] = %s\n", towBit, h[towBit].data());
      return false;
    }
    h[towBit] = table[i][0];
    MyPrintf("h[%d] = %s\n", towBit, table[i][0].data());
    MyPrintf("H[%s] = %d\n", table[i][0].data(), towBit);
  }
  MyPrintf("B = %d\n", B);
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      const int a = H[table[i][0]];
      const int b = H[table[0][j]];
      const int ab10 = a + b;
      string abStr;
      if (ab10 >= B) {
        const int V1 = ab10 / B;
        const int V0 = ab10 % B;
        abStr = h[V1] + h[V0];
        MyPrintf("%d >= %d: V1=%d h[V1]=%s, V0=%d h[V0]=%s +=%s\n", ab10, B, V1, h[V1].data(), V0, h[V0].data(), abStr.data());
      } else {
        abStr = h[ab10];
        MyPrintf("%d < %d: abStr = %s\n", ab10, B, abStr.data());
      }
      if (abStr != table[i][j]) {
        MyPrintf("i:%s->%d, j:%s->%d,  ab10=%d abStr = %s, table[%d][%d] = %s\n", table[i][0].data(), a,
                 table[0][j].data(), b, ab10, abStr.data(), i, j, table[i][j].data());
        return false;
      }
    }
  }

  return true;
}

void Solver() {  //
  scanf("%d", &n);
  table.resize(n, vector<string>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%s", str);
      table[i][j] = str;
    }
  }
  if (!Check()) {
    printf("ERROR!\n");
  } else {
    for (int i = 1; i < n; i++) {
      printf("%s=%d%c", table[0][i].data(), H[table[0][i]], i == n - 1 ? '\n' : ' ');
    }
    printf("%d\n", B);
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
