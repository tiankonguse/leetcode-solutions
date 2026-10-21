/*
ID: tiankonguse
TASK: file
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17722?contestId=358588
PATH: P17722 [SCP-S 2026] 档案 / file
submission:
*/
#define TASK "file"
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

ll n, m;
vector<ll> A;
vector<ll> B;
/*
// 思路6：根据性质1 和性质2的规律近一步推导。

默认编号 1 到 n
论证：对于 B 序列，谁应该在前面，谁应该在后面？
假设 B 序列都是一个数字，第一个序列有 b1 个数字，第二个序列有 b2个数字。A 中大于 b1 的有 x 个数字，大于 b2 的有 y 个数字


如果 b1 在前面，b2 在后面
则第一次代价是 1+2+3+...+n+x， 加上x是由于A中有 x 个数字都后移一位，编号都加1
第二次代价是 1+2+3+...+n+x+y，加上 y 是由于A中有 y 个数字再次后移一位，编号再次加1
总代价是 2*(1+2+3+...+n)+2*x+y。
与性质A一样，x 越小，应该越靠前

如果 B 序列有多个数字呢?  
可以发现，每个数字都会让 A 中大于它的数字都后移一位，编号也会增加 1。编号累计增加的值就是 B 序列中A 大于每个数字的个数之和。
同理，可以发现，多个数字依旧满足性质A的规律。

故，计算出每个序列导致编号增大的个数，然后排序，然后按上述方式计算
*/
void Solver() {  //
  scanf("%lld%lld", &n, &m);
  A.resize(n);
  B.resize(m);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
  }
  sort(A.begin(), A.end());


  for (int i = 0; i < m; i++) {
    ll L;
    scanf("%lld", &L);
    ll sum = 0;
    for (int j = 0; j < L; j++) {
      ll x;
      scanf("%lld", &x);
      ll cnt = A.end() - lower_bound(A.begin(), A.end(), x);
      sum += cnt; // x 让 A 中的 cnt 个数字都后移一位，编号都加1
    }
    B[i] = sum; 
  }
  sort(B.begin(), B.end());
  ll ans = 0;
  ll base = (1 + n) * n / 2;
  for (ll b : B) {
    base += b;
    ans += base;
  }
  printf("%lld\n", ans);
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
