/*
ID: tiankonguse
TASK: C. Dynamic Connectivity Offline C. 离线动态连接
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
desc: 进行路径压缩，记录下所有修改操作 Accepted	249 ms	6800 KB
*/
#define TASK "C-dynamic-connectivity-offline-v0"
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

int n, m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
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
vector<tuple<char, int, int, int, int>> queries;

vector<int> ans;
void InitQuery() {
  map<pair<int, int>, int> preOps;
  queries.reserve(m * 32);
  ans.reserve(m);
  for (int i = 0; i < m; i++) {
    char op[2];
    int u = 0, v = 0;
    scanf("%s", op);
    if (op[0] == '?') {
      queries.push_back({'?', i, ans.size(), u, v});
      ans.push_back(0);
    } else {
      scanf("%d%d", &u, &v);
      if (u > v) {
        swap(u, v);
      }
      if (op[0] == '+') {
        preOps[{u, v}] = i;
      } else {
        int r = i, l = preOps[{u, v}];
        queries.push_back({'.', l, r, u, v});
        preOps.erase({u, v});
      }
    }
  }

  for (auto [p, t] : preOps) {
    auto [u, v] = p;
    queries.push_back({'.', t, m, u, v});
  }
  sort(queries.begin(), queries.end(), [](auto& a, auto& b) { return get<1>(a) < get<1>(b); });
}

bool Intersects(int l, int r, int L, int R) {  //
  return (l < L && L < r) || (l < R && R < r);
}
void Work(const int l, const int r, const int startIndex, const int endIndex) {  // [l, r] [startIndex, endIndex)
  if (l == r) {
    dsu.Persist();
    for (int i = startIndex; i < endIndex; i++) {
      const auto& [op, L, R, u, v] = queries[i];
      if (op == '?' && L == l) {
        ans[R] = dsu.Count();
      } else if (op == '.' && L <= l && r <= R) {
        dsu.Union(u, v);
      }
    }
    dsu.Rollback();
    return;
  }

  dsu.Persist();
  for (int i = startIndex; i < endIndex; i++) {
    const auto& [op, L, R, u, v] = queries[i];
    if (op == '.' && L <= l && r <= R) {
      dsu.Union(u, v);
    } else if ((op == '?' && l <= L && L <= r) || (op == '.' && Intersects(l, r, L, R))) {
      queries.push_back(queries[i]);
    }
  }

  const int m = (l + r) / 2;
  Work(l, m, endIndex, queries.size());
  Work(m + 1, r, endIndex, queries.size());

  while (int(queries.size()) > endIndex) {
    queries.pop_back();
  }
  dsu.Rollback();
}
void Solver() {  //
  InitQuery();
  dsu.Init(n);
  Work(0, m, 0, queries.size());
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