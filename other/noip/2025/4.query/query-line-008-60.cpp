/*
ID: tiankonguse
TASK: query-A
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "query"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

inline void CheckUsacoTask() {
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
const int max3 = 2010, max4 = 50010, max5 = 500010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 20
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

int n, q;
ll preSums[max4];

int base2[max4];

inline ull Fix(ll k) {  //
  return ull(k);
}

const int maxLog = 16;
ll rmqMax[max4][maxLog];
ll rmqMin[max4][maxLog];

// rmq[l][i] = max(preSums[l], ..., preSums[l+2^i-1])  [l, l+2^i-1]
// max(a,..., b) = max(rmq[a][k], rmq[b-2^k+1][k])
inline ll MaxSum(const int a, const int b) {
  const int k = base2[b - a + 1];
  return max(rmqMax[a][k], rmqMax[b - (1 << k) + 1][k]);
}
inline ll MinSum(const int a, const int b) {
  const int k = base2[b - a + 1];
  return min(rmqMin[a][k], rmqMin[b - (1 << k) + 1][k]);
}

ll tmpDP[max5];
ll dp[max5];                                           // 最终的答案
inline void UpdateAns(const int i, const ll tmpAns) {  //
  // MyPrintf("i=%d update tmpAns %lld\n", i, tmpAns);
  dp[i] = max(dp[i], tmpAns);
}

// ll dpTmp[max5];
pair<ll, int> que[max5];  // 单调队列, {maxVal, pos}, 递减
int qL, qR;               // [qL, qR)

void SolverL(const int D, const int U, const int minDis, const int maxDis) {
  // MyPrintf("SolverL D=%d U=%d minDis=%d maxDis=%d\n", D, U, minDis, maxDis);
  // 第一步：计算以 i 为左端点，长度为 [D,U] 的所有极好区间的最大权值
  qL = 0, qR = 0;
  for (int i = 1; i <= n; i++) {
    // pop que[qL] if que[qL].second < i + D
    while (qL < qR && que[qL].second < i + D) {
      qL++;
    }

    int r = i + D;
    if (qL < qR) r = que[qR - 1].second + 1;
    while (r <= n && r <= i + U) {
      // pop que[qR - 1] if que[qR - 1].first <= preSums[r]
      while (qL < qR && que[qR - 1].first <= preSums[r]) {
        qR--;
      }
      que[qR++] = {preSums[r], r};
      r++;
    }
    if (qL == qR) {  // 没有答案
      tmpDP[i] = INT64_MIN;
    } else {
      tmpDP[i] = que[qL].first - preSums[i - 1];
    }
  }

  // 第二步：计算以 [i-maxDis+1,i-minDis+1] 为左端点，长度为 [D,U] 的所有极好区间的最大权值
  qL = 0, qR = 0;
  int l = 0, r = 0;
  for (int i = 1 + minDis; i <= n; i++) {
    // if (i - minDis < 1) continue;  // 无效区间
    // pop dpL[pos] if pos < i - maxDis
    while (qL < qR && que[qL].second < i - maxDis) {
      qL++;
    }

    const int j = i - minDis;
    const ll tmp = tmpDP[j];
    // add dpL[i-minDis]
    while (qL < qR && que[qR - 1].first <= tmp) {
      qR--;
    }
    que[qR++] = {tmp, j};
    UpdateAns(i, que[qL].first);
  }
}
void SolverR(int D, int U, int minDis, int maxDis) {
  // MyPrintf("SolverR D=%d U=%d minDis=%d maxDis=%d\n", D, U, minDis, maxDis);
  // 第一步：计算以 i 为右端点，长度为 [D,U] 的所有极好区间的最大权值
  qL = 0, qR = 0;
  for (int i = n; i >= 1; i--) {
    // pop que[qL] if que[qL].second > i - D
    while (qL < qR && que[qL].second > i - D) {
      qL++;
    }
    int r = i - D;
    if (qL < qR) r = que[qR - 1].second - 1;
    while (r >= 1 && r >= i - U) {
      // pop que[qR - 1] if que[qR - 1].first >= preSums[r-1]
      while (qL < qR && que[qR - 1].first >= preSums[r - 1]) {
        qR--;
      }
      que[qR++] = {preSums[r - 1], r};
      r--;
    }
    if (qL == qR) {  // 没有答案
      tmpDP[i] = INT64_MIN;
    } else {
      tmpDP[i] = preSums[i] - que[qL].first;
    }
  }

  // 第二步：计算以 [i+minDis-1,i+maxDis-1] 为右端点，长度为 [D,U] 的所有极好区间的最大权值
  qL = 0, qR = 0;
  int l = 0, r = 0;
  for (int i = n - minDis; i >= 1; i--) {
    // if (i + minDis > n) continue;  // 无效区间
    // pop dpL[pos] if pos > i + maxDis - 1
    if (qL < qR && que[qL].second > i + maxDis) {
      qL++;
    }
    const int j = i + minDis;
    const ll tmp = tmpDP[j];

    // add dpL[i+minDis-1]
    while (qL < qR && que[qR - 1].first <= tmp) {
      qR--;
    }
    que[qR++] = {tmp, j};
    UpdateAns(i, que[qL].first);
  }
}

/*
// 右下角顶点为 (i-L, i) 变成为 a 的正方向
f(i) = max(sum(i-L-a, i), ..., sum(i-L, i))  // 水平线
= max(sum(i) - sum(i-L-a-1), ..., sum(i) - sum(i-L-1));
= sum(i) - min(sum(i-L-a-1), ..., sum(i-L-1));

f(i+1) = max(sum(i-L-a, i+1), ..., sum(i-L, i+1))
= max(sum(i+1) - sum(i-L-a-1), ..., sum(i+1) - sum(i-L-1));
= sum(i+1) - min(sum(i-L-a-1), ..., sum(i-L-1));

max(f(i), ..., f(i+a))
 = max(
   sum(i) - min(sum(i-L-a-1), ..., sum(i-L-1))
   ...
   sum(i+a) - min(sum(i-L-a-1), ..., sum(i-L-1))
 )
= max(sum(i),..., sum(i+a)) - min(sum(i-L-a-1), ..., sum(i-L-1))
*/
void SolverSquare(int L, int a) {
  // MyPrintf("SolverSquare L=%d a=%d\n", L, a);
  if (a == 0) return;
  for (int i = 1 + L; i <= n; i++) {
    // if (i - L < 1) continue;
    ll tmp = MaxSum(i, min(n, i + a)) - MinSum(max(0, i - L - a - 1), i - L - 1);
    UpdateAns(i, tmp);
  }
}

ull Solver(int L, int R) {
  int a = (R - L) >> 1;  // 正方形边长
  for (int i = 1; i <= n; i++) {
    dp[i] = INT64_MIN;
  }
  if (L > 1) {
    SolverL(L - 1, R - 1, 0, L - 1);  // 梯形的左半部平行四边形
  }
  SolverL(L - 1 + a, R - 1, L - 1, L - 1 + a);  // 三角形右上的平行四边形
  SolverR(L - 1 + a, R - 1, 0, a);              // 三角形左下的平行四边形
  SolverSquare(L - 1, a);                       // 三角形内的正方形

  ull ans = 0;
  for (int i = 1; i <= n; i++) {
    // ll square = INT64_MIN;
    // if (i - (L - 1) >= 1) {
    //   square = MaxSum(i, min(n, i + a)) - MinSum(max(0, i - (L - 1) - a - 1), i - (L - 1) - 1);
    // }
    ans ^= Fix(dp[i] * i);
  }

  return ans;
}

void Init() {
  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    preSums[i] += preSums[i - 1];
  }
  for (int i = 0; i <= n; i++) {
    rmqMax[i][0] = preSums[i];
  }
  for (int k = 1; k < maxLog; k++) {
    for (int i = 0; i <= n; i++) {
      if (i + (1 << (k - 1)) > n) break;
      rmqMax[i][k] = max(rmqMax[i][k - 1], rmqMax[min(i + (1 << (k - 1)), n)][k - 1]);
    }
  }
  for (int i = 0; i <= n; i++) {
    rmqMin[i][0] = preSums[i];
  }
  for (int k = 1; k < maxLog; k++) {
    for (int i = 0; i <= n; i++) {
      if (i + (1 << (k - 1)) > n) break;
      rmqMin[i][k] = min(rmqMin[i][k - 1], rmqMin[min(i + (1 << (k - 1)), n)][k - 1]);
    }
  }
  base2[1] = 0;
  for (int i = 2; i <= n; i++) {
    base2[i] = base2[i >> 1] + 1;
  }
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &preSums[i]);
  }
  Init();
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%llu\n", Solver(l, r));
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
