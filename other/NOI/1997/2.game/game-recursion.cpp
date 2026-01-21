/*
ID: tiankonguse
TASK: game
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "game"
#define TASKEX "-recursion"

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
int debug_log = 1;
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

int n, m;
vector<vector<int>> nums;

// // dp[k][p0][p1][s0][s1] 前 min(p0,s1)-1 个位置，划分为 k 段
// {p0, s0} 代表第 1 段下个位置选择的是 p0 位置的 s0 面，如果之前继续往第 1 段添加时，需满足 <= s0
// {p1, s2} 代表第 k 段下个位置选择的是 p1 位置的 s1 面，如果之前继续往第 k 段添加时，需满足 <= s1
// p0=n 代表第 1 段还没有选择
// p1=n 代表第 k 段还没有选择
// dp0 代表其他段存在的最大答案, -2 代表不存在答案
// dpFirst 代表第 1 段的最大答案, -2 代表不存在答案
ll dpFirst[111][111][111][3][3];
ll dpOther[111][111][111][3][3];

ll DfsFirst(const int k, const int firstPos, const int lastPos, const int firstArea, const int lastArea) {
  int r = min(firstPos, lastPos) - 1;
  if (k == 0 && r < 0) return 0;  // 0 个元素划分 0 块，是一种划分，答案为 0
  if (r < 0 || r < k) return -2;
  ll& ret = dpFirst[k][firstPos][lastPos][firstArea][lastArea];
  if (ret != -1) {
    return ret;
  }
  ret = -2;

  // 选择1：加入第一段
  for (int rs = 0; rs < 3; rs++) {
    const int rsA = nums[r][rs];
    const int rsB = nums[r][(rs + 1) % 3];
    const int rsC = nums[r][(rs + 2) % 3];
    if (firstPos == n) {
      ll tmp = DfsFirst(k, r, lastPos, rs, lastArea);
      if (tmp != -2) {
        ret = max(ret, tmp + rsC);
      }
    } else {
      const int firstAreaA = nums[firstPos][firstArea];
      const int firstAreaB = nums[firstPos][(firstArea + 1) % 3];
      const int firstAreaC = nums[firstPos][(firstArea + 2) % 3];
      if ((rsA <= firstAreaA && rsB <= firstAreaB) || (rsA <= firstAreaB && rsB <= firstAreaA)) {
        ll tmp = DfsFirst(k, r, lastPos, rs, lastArea);
        if (tmp != -2) {
          ret = max(ret, tmp + rsC);
        }
      }
    }
  }

  // 选择2：加入第 k 段
  if (k > 0) {
    for (int rs = 0; rs < 3; rs++) {
      const int rsA = nums[r][rs];
      const int rsB = nums[r][(rs + 1) % 3];
      const int rsC = nums[r][(rs + 2) % 3];
      if (lastPos == n) {
        // 独立一段
        ll tmp = DfsFirst(k - 1, firstPos, r, firstArea, rs);
        if (tmp != -2) {
          ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
        }
        // 前面还有属于第 k 段的元素
        tmp = DfsFirst(k, firstPos, r, firstArea, rs);
        if (tmp != -2) {
          ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
        }
      } else {
        const int lastAreaA = nums[lastPos][lastArea];
        const int lastAreaB = nums[lastPos][(lastArea + 1) % 3];
        const int lastAreaC = nums[lastPos][(lastArea + 2) % 3];
        if ((rsA <= lastAreaA && rsB <= lastAreaB) || (rsA <= lastAreaB && rsB <= lastAreaA)) {
          // 前面还有属于第 k 段的元素
          ll tmp = DfsFirst(k, firstPos, r, firstArea, rs);
          if (tmp != -2) {
            ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
          }
          // 独立一段
          tmp = DfsFirst(k - 1, firstPos, r, firstArea, rs);
          if (tmp != -2) {
            ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
          }
        }
      }
    }
  }
  return ret;
}

ll DfsOther(const int k, const int firstPos, const int lastPos, const int firstArea, const int lastArea) {
  int r = min(firstPos, lastPos) - 1;
  if (k == 0 && r < 0) return 0;  // 0 个元素划分 0 块，是一种划分，答案为 0
  if (r < 0 || r < k) return -2;
  ll& ret = dpOther[k][firstPos][lastPos][firstArea][lastArea];
  if (ret != -1) {
    return ret;
  }
  ret = -2;

  // 选择1：加入第一段
  for (int rs = 0; rs < 3; rs++) {
    const int rsA = nums[r][rs];
    const int rsB = nums[r][(rs + 1) % 3];
    const int rsC = nums[r][(rs + 2) % 3];
    if (firstPos == n) {
      ll tmp = DfsOther(k, r, lastPos, rs, lastArea);
      if (tmp != -2) {
        ret = max(ret, tmp);
      }
    } else {
      const int firstAreaA = nums[firstPos][firstArea];
      const int firstAreaB = nums[firstPos][(firstArea + 1) % 3];
      const int firstAreaC = nums[firstPos][(firstArea + 2) % 3];
      if ((rsA <= firstAreaA && rsB <= firstAreaB) || (rsA <= firstAreaB && rsB <= firstAreaA)) {
        ll tmp = DfsOther(k, r, lastPos, rs, lastArea);
        if (tmp != -2) {
          ret = max(ret, tmp);
        }
      }
    }
  }

  // 选择2：加入第 k 段
  if (k > 0) {
    for (int rs = 0; rs < 3; rs++) {
      const int rsA = nums[r][rs];
      const int rsB = nums[r][(rs + 1) % 3];
      const int rsC = nums[r][(rs + 2) % 3];
      if (lastPos == n) {
        // 独立一段
        ll tmp = DfsFirst(k - 1, firstPos, r, firstArea, rs);
        if (tmp != -2) {
          ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
        }
        // 前面还有属于第 k 段的元素
        tmp = DfsFirst(k, firstPos, r, firstArea, rs);
        if (tmp != -2) {
          ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
        }
      } else {
        const int lastAreaA = nums[lastPos][lastArea];
        const int lastAreaB = nums[lastPos][(lastArea + 1) % 3];
        const int lastAreaC = nums[lastPos][(lastArea + 2) % 3];
        if ((rsA <= lastAreaA && rsB <= lastAreaB) || (rsA <= lastAreaB && rsB <= lastAreaA)) {
          // 前面还有属于第 k 段的元素
          ll tmp = DfsFirst(k, firstPos, r, firstArea, rs);
          if (tmp != -2) {
            ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
          }
          // 独立一段
          tmp = DfsFirst(k - 1, firstPos, r, firstArea, rs);
          if (tmp != -2) {
            ret = max(ret, tmp);  // rsC 不是第一段的，不能加入到答案中
          }
        }
      }
    }
  }
  return ret;
}
void Solver() {  //
  scanf("%d%d", &n, &m);
  nums.resize(n, vector<int>(3, 0));
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &nums[i][0], &nums[i][1], &nums[i][2]);
  }
  memset(dpFirst, -1, sizeof(dpFirst));  // 代表没有计算答案
  memset(dpOther, -1, sizeof(dpOther));  // 代表没有计算答案
  const ll ansFirst = DfsFirst(m, n, n, 0, 0);
  const ll ansOther = DfsOther(m, n, n, 0, 0);
  printf("%lld\n", max(ansFirst, ansOther));

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
