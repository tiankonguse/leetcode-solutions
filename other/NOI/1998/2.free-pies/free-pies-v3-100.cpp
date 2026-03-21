/*
ID: tiankonguse
TASK: free-pies
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "free-pies"
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

class TreeArray {
 public:
  void Init(int n_) {  // [1,n]
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll QueryMax(int x) {  // [1,n]
    ll s = 0;
    while (x > 0) {
      s = max(s, c[x]);
      x -= Lowbit(x);
    }
    return s;
  }

  void SetVal(int x, ll v) {  // [1,n]
    while (x <= n) {
      c[x] = max(c[x], v);
      x += Lowbit(x);
    }
  }

 private:
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};

ll w, n;
vector<tuple<ll, ll, ll>> nums;
vector<tuple<ll, ll, ll>> points;

void MergeSameData() {
  sort(nums.begin(), nums.end());
  // 合并相同的 <t,p>
  int last = 0;
  for (int i = 1; i < n; i++) {
    if (get<0>(nums[i]) == get<0>(nums[last]) && get<1>(nums[i]) == get<1>(nums[last])) {
      get<2>(nums[last]) += get<2>(nums[i]);
    } else {
      nums[++last] = nums[i];
    }
  }
  n = last + 1;
  nums.resize(n);
}
void TransformData() {
  /*
      abs(pi - pj) <= (tj - ti) * 2
      1) pi - pj <= (tj - ti) * 2
         pi - pj <= tj * 2 - ti * 2
         ti * 2 + pi <= tj * 2 + pj

    2)   pj - pi <= (tj - ti) * 2
         pj - pi <= tj * 2 - ti * 2
         2 * ti - pi <= tj * 2 - pj
  */
  points.resize(n);
  for (int i = 0; i < n; i++) {
    auto [ti, pi, vi] = nums[i];
    ll xi = ti * 2 + pi;
    ll yi = ti * 2 - pi;
    points[i] = make_tuple(xi, yi, vi);
  }
}

unordered_map<ll, ll> mp;
vector<ll> ys;
int m;
void Discretization() {
  for (int i = 0; i < n; i++) {
    auto [xi, yi, vi] = points[i];
    ys.push_back(yi);
  }
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  m = ys.size();
  for (int i = 0; i < m; i++) {
    mp[ys[i]] = i + 1;
  }
}

TreeArray tree;

ll SolverPartialOrder() {
  sort(points.begin(), points.end());
  tree.Init(m);  // [1,m]
  ll ans = 0;
  for (auto [x, y, v] : points) {
    ll offset = mp[y];
    ll newVal = tree.QueryMax(offset) + v;
    tree.SetVal(offset, newVal);
    ans = max(ans, newVal);
  }
  return ans;
}

void Solver() {  //
  scanf("%lld%lld", &w, &n);
  nums.resize(n);
  for (int i = 0; i < n; ++i) {
    ll t, p, v;
    scanf("%lld%lld%lld", &t, &p, &v);
    nums[i] = make_tuple(t, p, v);
  }
  MergeSameData();
  TransformData();
  Discretization();

  printf("%lld\n", SolverPartialOrder());
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
