/*
ID: tiankonguse
TASK: CrossingRiver
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "CrossingRiver"
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

int L;
int S, T, M;
vector<int> dp;
vector<int> nums;
unordered_map<int, int> mp;
set<int> stones;

vector<int> ST;
int stLast = 0;
void InitST(int S, int T) {  //
  int maxLen = 100;
  ST.clear();
  ST.resize(maxLen, 0);
  ST[0] = 1;
  for (int i = 0; i < maxLen; i++) {
    if (ST[i] == 0) {
      stLast = i;
      continue;
    }
    for (int j = i + S; j <= i + T && j < maxLen; j++) {
      ST[j] = 1;
    }
  }
  MyPrintf("S=%d T=%d stLast = %d\n", S, T, stLast);
}

int IsStone(int i) {  //
  return stones.count(nums[i]);
}
bool IsGoTo(int i, int j) {  //
  int dis = j - i;
  if (S == T) {  //
    return dis % S == 0;
  }
  if (dis > stLast) {
    return true;
  }
  return ST[dis];
}

void Solver() {  //

  //   for (int S = 1; S <= 10; S++) {
  //     for (int T = S + 1; T <= 10; T++) {
  //       InitST(S, T);
  //     }
  //   }

  scanf("%d", &L);
  scanf("%d%d%d", &S, &T, &M);

  InitST(S, T);

  mp[0] = 0;
  mp[L] = 0;
  for (int i = 0; i < M; i++) {
    int v;
    scanf("%d", &v);
    mp[v] = 1;
    stones.insert(v);
    for (int j = 0; j <= T; j++) {
      mp[L + j] = 0;  // 最后插入 T 个空间
      int p0 = v - j;
      if (p0 > 0 && !mp.count(p0)) {
        mp[p0] = 0;
      }
      int p1 = v + j;
      if (!mp.count(p1)) {
        mp[p1] = 0;
      }
    }
  }
  int n = mp.size();
  nums.reserve(n);
  for (auto [k, v] : mp) {
    nums.push_back(k);
  }
  sort(nums.begin(), nums.end());
  for (int i = 0; i < n; i++) {
    mp[nums[i]] = i;
  }

  // 方法1：暴力枚举
  //   dp.resize(L + 1, INF);
  //   dp[0] = 0;
  //   for (int i = 0; i < L; i++) {
  //     for (int j = S; j <= T; j++) {
  //       int p = min(i + j, L);
  //       if (mp.count(p)) {
  //         dp[p] = min(dp[p], dp[i] + 1);
  //       } else {
  //         dp[p] = min(dp[p], dp[i]);
  //       }
  //     }
  //   }
  //   printf("%d\n", dp[L]);
  // 方法2：离散化

  stones.insert(L + 2 * T + 1);  // 添加一个虚拟的石头
  dp.resize(n + 1, INF);
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    const int pi = nums[i];                            // 压缩后的第 i 个位置
    const int nextStonePos = *stones.upper_bound(pi);  // 下个石头的位置
    MyPrintf("i=%d pi=%d isStone=%d nextStonePos=%d\n", i, pi, IsStone(i), nextStonePos);
    for (int j = 1; j <= T; j++) {
      const int ij = min(i + j, n - 1);
      const int pj = nums[ij];
      const int dis = pj - pi;
      if (dis < S) {
        // 什么都不做
      } else if (dis >= S && dis <= T) {
        dp[ij] = min(dp[ij], dp[i] + IsStone(ij));
      } else {
        assert(pj < nextStonePos);  // 不可能，已经在所有石头前后插入 T 个空间
        // 超过了 T
        if (IsGoTo(pi, pj)) {  // pi 到 pj 之间没有石头
          dp[ij] = min(dp[ij], dp[i]);
        }
      }
    }
  }
  printf("%d\n", dp[n - 1]);
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
