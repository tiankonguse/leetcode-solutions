/*
ID: tiankonguse
TASK: A. DSU with rollback  A. 带回滚的 DSU
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
desc: 持久化时复制所有状态，Time limit exceeded on test 7
*/
#define TASK "A-DSU-with-rollback"
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
  vector<vector<int>> pre;
  vector<vector<int>> nums;
  vector<int> sums;
  int n;

  void Init(int n) {
    this->n = n;
    pre.resize(n + 1);
    nums.resize(n + 1);
    sums.reserve(n + 1);
    for (int i = 1; i <= n; i++) {
      pre[i].push_back(i);
      nums[i].push_back(1);
    }
    sums.push_back(n);  // 时间 t 联通块个数
  }
  int Get(const int u) {
    while (pre[u].back() != pre[pre[u].back()].back()) {  
      pre[u].back() = Get(pre[u].back());
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
      pre[v].back() = u;
      nums[u].back() += nums[v].back();
      sums.back()--;
    }
    return sums.back();
  }
  int Persist() {
    for (int i = 1; i <= n; i++) {
      pre[i].push_back(pre[i].back());
      nums[i].push_back(nums[i].back());
    }
    sums.push_back(sums.back());
    return sums.back();
  }
  int Rollback() {  //
    for (int i = 1; i <= n; i++) {
      pre[i].pop_back();
      nums[i].pop_back();
    }
    sums.pop_back();
    return sums.back();
  }
};

Dsu dsu;
int b, e;
char op[20];
void Solver() {  //
  dsu.Init(n);
  for (int i = 1; i <= m; i++) {
    scanf("%s", op);
    if (op[0] == 'u') {
      scanf("%d%d", &b, &e);
      printf("%d\n", dsu.Union(b, e));
    } else if (op[0] == 'p') {
      dsu.Persist();
    } else {
      printf("%d\n", dsu.Rollback());
    }
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