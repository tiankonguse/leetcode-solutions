/*
ID: tiankonguse
TASK: query-A
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:

case 1: Accepted, cost 1ms
case 2: Accepted, cost 2ms
case 3: Accepted, cost 2ms
case 4: Accepted, cost 27ms
case 5: Accepted, cost 350ms
case 6: Accepted, cost 498ms
case 7: Accepted, cost 479ms
case 8: Accepted, cost 625ms
case 9: Accepted, cost 615ms
case 10: Accepted, cost 608ms
case 11: Accepted, cost 439ms
case 12: Accepted, cost 448ms
case 13: Accepted, cost 384ms
case 14: Accepted, cost 517ms
case 15: Accepted, cost 520ms
case 16: Accepted, cost 953ms
case 17: Accepted, cost 1002ms
case 18: Accepted, cost 1048ms
case 19: Accepted, cost 963ms
case 20: Accepted, cost 802ms
Total: 20 / 20, 得分： 100

4
2 4 -5 1
1
1 4
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

struct MonoQueue {
  int idx[max4];
  ll val[max4];
  int l, r;
  inline void reset() { l = 0, r = 0; }
  inline void push_back(ll v, int pos) {
    while (l < r && val[r - 1] <= v) r--;
    val[r] = v;
    idx[r] = pos;
    r++;
  }
  inline void pop(int pos) {
    while (l < r && idx[l] < pos) l++;
  }
  inline ll front() { return val[l]; }
  inline ll back() { return val[r - 1]; }
  inline bool empty() { return l == r; }
} Q[3];

int n, q;
ll preSums[max4];

// int base2[max4];
// void InitBase2(int n) {
//   base2[1] = 0;
//   for (int i = 2; i <= n; i++) {
//     base2[i] = base2[i >> 1] + 1;
//   }
// }
// 使用内建函数计算 ⌊ log_2 x ⌋
// inline int lg2(int x) { return 31 - __builtin_clz(x); }
// inline int Log2(int x) { return base2[x]; }
inline int Lg(int x) { return __lg(x); }
inline int Log(int x) { return Lg(x); }
const int kMaxLog = 16;
struct SparseTableMax {
  inline ll Max(const int a, const int b) { return a > b ? a : b; }
  // nums[1...n]
  void Init(int n, ll nums[]) {
    int maxLog = Log(n) + 1;
    st[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      st[0][i] = nums[i];
    }
    for (int k = 1; k < maxLog; k++) {
      for (int i = 0; i + (1 << k) - 1 <= n; i++) {
        st[k][i] = Max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
      }
    }
  }
  inline ll Query(const int a, const int b) {
    const int k = Log(b - a + 1);
    return Max(st[k][a], st[k][b - (1 << k) + 1]);
  }

 private:
  ll st[kMaxLog][max4];
};

struct SparseTableMin {
  inline ll Min(const int a, const int b) { return a < b ? a : b; }
  // nums[1...n]
  void Init(int n, ll nums[]) {
    int maxLog = Log(n) + 1;
    st[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      st[0][i] = nums[i];
    }
    for (int k = 1; k < maxLog; k++) {
      for (int i = 0; i + (1 << k) - 1 <= n; i++) {
        st[k][i] = Min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
      }
    }
  }
  inline ll Query(const int a, const int b) {
    const int k = Log(b - a + 1);
    return Min(st[k][a], st[k][b - (1 << k) + 1]);
  }

 private:
  ll st[kMaxLog][max4];
};

SparseTableMax stMax;
SparseTableMin stMin;

// rmq[l][i] = max(preSums[l], ..., preSums[l+2^i-1])  [l, l+2^i-1]
// max(a,..., b) = max(rmq[a][k], rmq[b-2^k+1][k])
inline ll MaxSum(const int a, const int b) { return stMax.Query(a, b); }
inline ll MinSum(const int a, const int b) { return stMin.Query(a, b); }

ll SolverLEx(const int q, const int j, const int D, const int U, const int W) {
  auto& Qq = Q[q];
  // 第一步：计算以 i 为左端点，长度为 [D,U] 的所有极好区间的最大权值
  // 第二步：计算以 [i-maxDis+1,i-minDis+1] 为左端点，长度为 [D,U] 的所有极好区间的最大权值
  // if (W == 0) return INT64_MIN;  // 无效区间
  Qq.pop(j - W);
  if (j + D <= n) {
    ll tmp = MaxSum(j + D, min(j + U, n)) - preSums[j - 1];
    Qq.push_back(tmp, j);  // add dpL[i-minDis]
  }
  if (!Qq.empty()) return Qq.front();
  return INT64_MIN;
}
ll SolverR(const int q, const int i, const int D, const int U, const int W) {
  auto& Qq = Q[q];
  // 第一步：计算以 i 为右端点，长度为 [D,U] 的所有极好区间的最大权值
  // 第二步：计算以 [i+minDis-1,i+maxDis-1] 为右端点，长度为 [D,U] 的所有极好区间的最大权值
  Qq.pop(i);
  const int j = i + W;
  if (j <= n && j - D >= 1) {
    ll tmp = preSums[j] - MinSum(max(0, j - U - 1), j - D - 1);
    Qq.push_back(tmp, j);
  }
  if (!Qq.empty()) return Qq.front();
  return INT64_MIN;
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
inline ll SolverSquare(const int i, const int L, const int a) {
  if (i - L < 1) return INT64_MIN;
  ll tmp = MaxSum(i, min(n, i + a)) - MinSum(max(0, i - L - a - 1), i - L - 1);
  return tmp;
}

ull Solver(int L, int R) {
  const int a = (R - L) >> 1;  // 正方形边长
  Q[0].reset();
  Q[1].reset();
  Q[2].reset();
  ull ans = 0;
  MyPrintf("L=%d R=%d a=%d\n", L, R, a);
  for (int i = 1; i <= n; i++) {
    ll v1 = SolverLEx(0, i, L - 1, R - 1, L - 1);          // 计算梯形的左半部平行四边形
    ll v2 = SolverLEx(1, i, L - 1 + a, R - 1, a + L - 1);  // 计算三角形左半部平行四边形
    ll v3 = SolverR(2, i, L - 1 + a, R - 1, a);            // 计算三角形右半部平行四边形
    ll v4 = SolverSquare(i, L - 1, a);                     // 三角形内的正方形
    ll v = max(max(v1, v2), max(v3, v4));
    MyPrintf("i=%d, v1=%lld v2=%lld v3=%lld v4=%lld v=%lld\n", i, v1, v2, v3, v4, v);
    ans ^= ull(v) * i;
  }
  return ans;
}

void Init() {
  // InitBase2(n);
  stMax.Init(n, preSums);
  stMin.Init(n, preSums);
}

void Solver() {  //
  scanf("%d", &n);
  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &preSums[i]);
    preSums[i] += preSums[i - 1];
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
