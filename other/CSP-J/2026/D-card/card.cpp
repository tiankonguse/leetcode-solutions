/*
ID: tiankonguse
TASK: card
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17830
PATH: P17830 [CSP-J 2026] 纸牌游戏 / card
submission:
*/
#define TASK "card"
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
#define USACO_TASK_FILE 0
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

/*
card-68-TLE.cpp 中已经推导出了三个性质：
1）假设第一个数字是 x，位置是 L，则 x 肯定是答案。  
2）x 的最后一个位置是 R, 则 `[l,R]` 之间的其他数字都会被消除。
3）接下来从 `R+1` 开始，又可以当做第一个数字来按题意消除了。  


暴力做法是每个位置贪心枚举，复杂度 `O(n*m)`  

接下来分析暴力做法为啥会超时，该怎么优化。  


观察相同的数字，可以发现，如果数字 x 被保留下来，则一定停留在位置 R，之后都会遵循性质3 从 `R+1` 重新开始消除。  
故，对于相同数字，存在公共的 `R+1`后缀，可以状态合并避免重复运算。  


状态定义：`dp[i]` 有多少个前缀前面都消除了，然后以 i 位置重新开始消除。  

状态转移方程：

如果当前位置的数字不是最后一个，则可以合并到最后一个位置。
如果当前位置的数字是最后一个，则下个位置可以重新开始消除。

if(lastPos[v] != i){
    dp[lastPos[v]] += dp[i];
} else {
    dp[lastPos[v] + 1] += dp[i];
}

更新答案：如果一个数字是最后一个，则更新答案
if(lastPos[v] == i){
    ans[v] = dp[i];
}
    
复杂度：`O(n)`  

*/

int n, m;
vector<int> nums;
vector<int> lastPos;  // 邻接表

vector<int> ans;
vector<int> dp;
void SkipSolver() {
  // 利用动态规划，避免重复运算
  for (int i = 0; i < n; i++) {
    const int v = nums[i];  // 作为第一个，肯定会保留下来
    const int last = lastPos[v];
    dp[i]++;
    if (last == i) {  // 作为最后一个，更新答案
      ans[v] = dp[i];
      dp[last + 1] += dp[i];
    } else {
      dp[last] += dp[i];
    }
  }
}

void Solver() {
  scanf("%d%d", &n, &m);
  nums.resize(n);
  lastPos.resize(m + 1, n);
  dp.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
    lastPos[nums[i]] = i;
  }
  ans.resize(m + 1, 0);
  SkipSolver();
  for (int i = 1; i <= m; i++) {
    printf("%d%c", ans[i], i == m ? '\n' : ' ');
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
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  MyPrintf("my 用时: %.0lfms\n", costTime);
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
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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
