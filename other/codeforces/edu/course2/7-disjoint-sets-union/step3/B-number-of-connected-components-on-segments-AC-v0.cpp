/*
ID: tiankonguse
TASK: B. Number of Connected Components on Segments B. 段上连接组件的数量
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/B
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
desc: 左边界按 sm 进行分组，相同组按右边界排序，不同组按左边界排序，分别对每个分组为起始位置的查询进行处理
*/
#define TASK "B-number-of-connected-components-on-segments"
#define TASKEX ""

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

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

int n, m, k;
vector<pair<int, int>> edges;
vector<tuple<int, int, int>> querys;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  edges.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &edges[i].first, &edges[i].second);
  }
  scanf("%d", &k);
  querys.reserve(k);
  for (int i = 0; i < k; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    l--, r--;
    querys.push_back({i, l, r});
  }
}

struct Dsu {
  enum { OP_UNION = 1, OP_PATH_COMPRESS = 2 };
  vector<vector<int>> pre;
  vector<vector<int>> nums;
  vector<int> sums;
  vector<tuple<int, int, int>> timeline;  // 储存union修改记录，用于回滚
  vector<int> checkpoints;

  void Init(int n) {
    timeline.reserve(n * 2);
    checkpoints.reserve(n * 2);
    sums.reserve(n + 1);

    pre.resize(n + 1);
    nums.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      pre[i].push_back(i);
      nums[i].push_back(1);
    }
    sums.push_back(n);
  }
  int Get(const int u) {  // 第一个版本，先不路径压缩
    if (pre[u].back() != pre[pre[u].back()].back()) {
      const int root = Get(pre[u].back());
      timeline.push_back({OP_PATH_COMPRESS, u, 0});
      pre[u].push_back(root);
    }
    return pre[u].back();
  }
  int Union(int u, int v) {  // u->v
    u = Get(u);
    v = Get(v);
    if (u != v) {  // 小树合并到大树上
      if (nums[u].back() < nums[v].back()) {
        swap(u, v);
      }
      timeline.push_back({OP_UNION, u, v});
      pre[v].push_back(u);
      nums[u].push_back(nums[u].back() + nums[v].back());
      sums.back()--;
    }
    return sums.back();
  }
  int Persist() {
    checkpoints.push_back(timeline.size());
    sums.push_back(sums.back());
    return sums.back();
  }
  int Rollback() {  //
    while (int(timeline.size()) > checkpoints.back()) {
      auto [op, u, v] = timeline.back();
      if (op == OP_UNION) {
        pre[v].pop_back();
        nums[u].pop_back();
      } else {
        pre[u].pop_back();
      }
      timeline.pop_back();
    }
    checkpoints.pop_back();
    sums.pop_back();
    return sums.back();
  }
  int Count() { return sums.back(); }
};

Dsu dsu;
void Solver() {  //
  dsu.Init(n);

  const int sm = max(int(sqrt(m)), 10);  // 最少 10 个一组
  // printf("sm=%d\n", sm);
  vector<int> minLeft(m + 1, m);
  for (int i = m - 1; i >= 0; i--) {
    minLeft[i / sm] = i;
  }

  // 左边界按 sm 进行分组，相同组按右边界排序，不同组按左边界排序
  sort(querys.begin(), querys.end(), [&sm](tuple<int, int, int>& a, tuple<int, int, int>& b) {
    auto [ai, al, ar] = a;
    auto [bi, bl, br] = b;
    if (al / sm == bl / sm) {
      return ar < br;
    } else {
      return al < bl;
    }
  });

  vector<int> ans(k, 0);

  dsu.Persist();  // 先持久化保存记录
  int pre_sm_l = -1;
  int pre_sm_r = -1;  // (l,r) 之内的 blcok 都已经计算
  for (const auto& [qi, ql, qr] : querys) {
    const int sm_l = ql / sm;  // 左边界的起始位置
    const int sm_r = qr / sm;  // 左边界的起始位置
    // printf("qi=%d ql=%d qr=%d sm_l=%d sm_r=%d pre_sm_l=%d\n", qi, ql, qr, sm_l, sm_r, pre_sm_l);
    if (pre_sm_l != sm_l) {
      dsu.Rollback();  // 所有的 black 操作都恢复，重新计算
      dsu.Persist();   // 先持久化保存记录
      pre_sm_l = sm_l;
      pre_sm_r = sm_l + 1;
    }
    // printf("pre_sm_l=%d pre_sm_r=%d\n", pre_sm_l, pre_sm_r);

    if (pre_sm_r < sm_r) {  // [pre_sm_r, sm_r-1] block 都可以进行持久化
      // printf("add block \n");
      for (int i = minLeft[pre_sm_r]; i / sm < sm_r; i++) {
        auto [u, v] = edges[i];
        dsu.Union(u, v);
      }
      pre_sm_r = sm_r;
    }

    dsu.Persist();  // 修改前，先持久化

    if (sm_l == sm_r) {
      for (int i = ql; i <= qr; i++) {
        auto [u, v] = edges[i];
        dsu.Union(u, v);
      }
    } else {
      for (int i = minLeft[sm_r]; i <= qr; i++) {  // 右半部
        auto [u, v] = edges[i];
        dsu.Union(u, v);
      }
      for (int i = ql; i < minLeft[sm_l + 1]; i++) {  // 左半部
        auto [u, v] = edges[i];
        dsu.Union(u, v);
      }
    }
    ans[qi] = dsu.Count();

    dsu.Rollback();  // 计算完成，恢复持久化
  }
  for (auto v : ans) {
    printf("%d\n", v);
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/