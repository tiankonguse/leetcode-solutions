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
const int max3 = 2010, max4 = 20010, max5 = 500010, max6 = 2000010;

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
ll preSums[max5];
// ll sufSums[max5];
ll nums[max5];

// dpL[i] = max(sums[i,L], ..., sums[i,R])
// dpLL[i] = max(dpL[i-L+1], ..., dpL[i]);
ll dpL[max5];  // dpL[i]: 以 i 为左端点的所有极好区间的最大权值
ll dpR[max5];  // dpR[i]: 以 i 为右端点的所有极好区间的最大权值
__int128_t pow2_64 = (__int128_t(1) << 64);
int base2[max5];

ull Fix(ll k) {
  ull kk = 0;
  if (k < 0) {
    __int128_t t = k;
    t += pow2_64;
    kk = t;
  } else {
    kk = k;
  }
  return kk;
}

ll rmq[max5][20];

// rmq[l][i] = max(preSums[l], ..., preSums[l+2^i-1])  [l, l+2^i-1]
// max(a,..., b) = max(rmq[a][k], rmq[b-2^k+1][k])
ll MaxSum(int a, int b) {
  int k = base2[b - a + 1];
  return max(rmq[a][k], rmq[b - (1 << k) + 1][k]);
}

deque<pair<ll, int>> queLeft;
deque<tuple<ll, int, int>> queRight;
void AddLeft(ll sum, int r) {
  while ((!queLeft.empty()) && preSums[r] - sum >= preSums[queLeft.back().second] - queLeft.back().first) {
    queLeft.pop_back();  // 整体单调性
  }
  queLeft.push_back({sum, r});
}
void AddRight(const ll newSum, int newL, const int newR) {
  while (!queRight.empty()) {
    const auto [oldSum, oldL, oldR] = queRight.back();
    const ll oldMaxSum = MaxSum(oldL, oldR);
    const ll newMaxSum = MaxSum(newL, newR);
    if (newMaxSum - newSum < oldMaxSum - oldSum) {  // 保持整体单调性，递减
      break;
    }
    MyAssert(oldR + 1 == newL);  // 预期是连续的
    newL = oldL;                 // 区间不需要连续，直接删除这个区间
    queRight.pop_back();
  }
  queRight.push_back({newSum, newL, newR});
}
// queLeft + queRight: preSums[second] - first 单调递减
// queRight: first 单调递增， first 相等时，preSums[second] 单调递减
ull Solver(const int L, const int R) {
  while (!queLeft.empty()) queLeft.pop_back();
  while (!queRight.empty()) queRight.pop_back();
  if (L < R) {
    queRight.push_back({0, L, R - 1});
  }
  for (int i = 1; i <= n; i++) {  // i-1 -> i
    // 第一步：queLeft 里 [?, i-1] 区间需要弹出
    if ((!queLeft.empty()) && queLeft.front().second == i - 1) {
      queLeft.pop_front();
    }

    // 第二步: queRight 里 [i, i+L-1], ..., [i, i+R-2] 区间更新为更小的 preSums[i - 1] 值
    {
      ll newSum = preSums[i - 1];
      int newL = i + R - 1, newR = i + R - 1;
      while ((!queRight.empty()) && get<0>(queRight.back()) >= newSum) {  // 右半部单调递增
        auto [oldSum, oldL, oldR] = queRight.back();
        queRight.pop_back();
        newL = oldL;
      }
      if (newL <= n) {
        newR = min(newR, n);
        AddRight(newSum, newL, newR);
      }
    }

    // 第三步：queRight 里 [?, i+L-1, ?] 区间需要转移到 queLeft， 但依旧需要保持整体单调性
    if (!queRight.empty()) {
      MyAssert(get<1>(queRight.front()) == i + L - 1);  // 非空时，一定存在 i+L-1
    }
    if (!queRight.empty() && get<1>(queRight.front()) == i + L - 1) {
      auto [newSum, newL, newR] = queRight.front();
      queRight.pop_front();
      AddLeft(newSum, newL);
      if (newL != newR) {
        newL++;
        // queRight 也需要保持单调性, 有可能 newL 移出去后，第一个就不是最优值了
        if (!queRight.empty()) {
          const auto [oldSum, oldL, oldR] = queRight.front();
          queRight.pop_front();
          MyAssert(newSum < oldSum);
          MyAssert(newR + 1 == oldL);
          ll oldMaxSum = MaxSum(oldL, oldR);
          ll newMaxSum = MaxSum(newL, newR);
          if (newMaxSum - newSum > oldMaxSum - oldSum) {  // 第一个依旧是最优，入队
            queRight.push_front({oldSum, oldL, oldR});
            queRight.push_front({newSum, newL, newR});
          } else {
            // 不是最优，不需要入队
            queRight.push_front({oldSum, newL, oldR});  // 合并到后面
          }
        } else {
          queRight.push_front({newSum, newL, newR});
        }
      }
    }

    // 第四步：更新 dpL[i]
    dpL[i] = preSums[queLeft.front().second] - queLeft.front().first;  // 可以保证 queLeft 肯定非空
    if (!queRight.empty()) {                                           // 有可能左侧不是最优的
      auto [oldSum, oldL, oldR] = queRight.front();
      dpL[i] = max(dpL[i], MaxSum(oldL, oldR) - oldSum);
    }
    MyPrintf("i=%d, dpL=%lld\n", i, dpL[i]);
  }

  ull ans = 0;
  for (int i = 1; i <= n; i++) {
    ll k = dpL[i];
    ans ^= Fix(k * i);
  }
  return ans;
}

void Init() {
  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    preSums[i] = preSums[i - 1] + nums[i];
  }
  for (int i = 1; i <= n; i++) {
    rmq[i][0] = preSums[i];
  }
  for (int k = 1; k < 20; k++) {
    for (int i = 1; i <= n; i++) {
      rmq[i][k] = max(rmq[i][k - 1], rmq[min(i + (1 << (k - 1)), n)][k - 1]);
    }
  }
  base2[1] = 0;
  for (int i = 2; i <= n; i++) {
    base2[i] = base2[i / 2] + 1;
  }
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &nums[i]);
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
