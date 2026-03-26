/*
ID: tiankonguse
TASK: budget
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "budget"
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

const double pi = acos(-1.0), eps = 1e-14;
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

// 距离S，油箱容量C，每升汽油行驶距离L，起始位置油价P
double S, C, L, P;
int N;
pair<double, double> nums[10];  // <距离D，油价P>
double ans;
bool Check() {
  ans = 0;
  if (S <= eps) {  // 两个城市相同，不需要费用
    return true;
  }
  if (C <= eps || L <= eps) {
    return false;  // 油箱容量为0，无法行驶
  }
  // 策略：每次都加满油并记录油价，遇到更便宜的油，剩余多少油就返回不加这些油，然后在更便宜的油站加满
  deque<pair<double, double>> que;  // <p, c*L> 价格为 p 的油有 c 升
  double left = 0;
  auto Add = [&que, &left](double p) {
    while (!que.empty()) {
      auto [p2, c2] = que.back();
      if (p2 > p + eps) {
        que.pop_back();
        ans -= p2 * c2;
        left -= c2;
      } else {
        break;
      }
    }
    double gap = C * L - left;
    ans += p * gap;
    left += gap;
    if (que.empty() || que.back().first < p) {
      que.push_back(make_pair(p, gap));
    } else {
      que.back().second += gap;
    }
  };
  Add(P);
  double pos = 0;
  for (int i = 0; i <= N; i++) {
    auto [di, pi] = nums[i];
    // 判断是否可以从 pos 开到 di
    if (di - pos > C * L + eps) return false;
    double need = di - pos;
    if (need > eps) {
      // 如果可以到达，开过来的时候，优先使用 que 里面更便宜的油
      while (!que.empty()) {
        auto [p2, c2] = que.front();
        if (c2 + eps <= need) {
          need -= c2;
          que.pop_front();
          continue;
        }
        que.front().second -= need;
        break;
      }
      left -= need;
      Add(pi);
      pos = di;
    }
  }

  return true;
}
void Solver() {  //
  scanf("%lf%lf%lf%lf%d", &S, &C, &L, &P, &N);
  for (int i = 0; i < N; i++) {
    scanf("%lf%lf", &nums[i].first, &nums[i].second);
  }
  nums[N] = make_pair(S, 0);
  sort(nums, nums + N + 1);
  if (Check()) {
    // 四舍五入保留2位小数
    printf("%.2lf\n", ans / L);
  } else {
    printf("No Solution\n");
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
