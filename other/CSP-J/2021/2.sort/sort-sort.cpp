/*
ID: tiankonguse
TASK: sort
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7910
PATH:  P7910 [CSP-J 2021] 插入排序
submission:
*/
#define TASK "sort"
#define TASKEX "-sort"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
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
#ifdef USACO_LOCAL_JUDGE
#define USACO_TASK_FILE 4
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
}

/*
线段树：单点更新，区间查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
vector<int> nums;
vector<pair<int, int>> exNums;
bool isSorted = true;

void Solver() {  //
  int n, Q;
  nums.clear();
  exNums.clear();

  scanf("%d%d", &n, &Q);
  nums.resize(n + 1);
  exNums.reserve(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &nums[i]);
    exNums.push_back({nums[i], i});
  }
  sort(exNums.begin(), exNums.end());

  auto removePos = [](int v, int x) { isSorted = false; };
  auto addPos = [](int v, int x) { isSorted = false; };
  auto searchPos = [&n](int v, int x) -> int {
    if (!isSorted) {
      isSorted = true;
      for (int i = 1; i <= n; i++) {
        exNums[i - 1] = {nums[i], i};
      }
      sort(exNums.begin(), exNums.end());
    }
    pair<int, int> p = {v, x};
    auto it = lower_bound(exNums.begin(), exNums.end(), p);
    return it - exNums.begin() + 1;  // 如果是第一个，
  };
  while (Q--) {
    int op, x, v = 0;
    scanf("%d%d", &op, &x);
    if (op == 1) {
      scanf("%d", &v);
      const int V = nums[x];
      removePos(V, x);
      addPos(v, x);
      nums[x] = v;

    } else {
      v = nums[x];
      int ans = searchPos(v, x);
      printf("%d\n", ans);
    }
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t1 = std::chrono::steady_clock::now();
#endif
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
  }
#endif
  return 0;
}

/*

*/