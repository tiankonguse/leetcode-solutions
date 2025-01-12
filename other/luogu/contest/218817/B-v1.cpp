/*
ID: tiankonguse
TASK: T549580 【MX-X7-T3】[LSOT-3] 寄存器
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/T561109?contestId=218816
PATH:
submission: https://github.com/tiankonguse/leetcode-solutions/
*/
#define TASK "B"
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

int n;
vector<int> nums;
vector<vector<int>> g;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &n);
  nums.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &nums[i]);
  }
  g.resize(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

int Search() {  //
  vector<int> que;
  que.reserve(n);
  vector<int> childNums(n + 1, 0);
  vector<int> delFlag(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    childNums[i] = g[i].size();
    if (childNums[i] == 1) {
      que.push_back(i);
    }
  }

  int ans = 0;
  while (!que.empty()) {
    int u = que.back();
    que.pop_back();
    if (childNums[u] == 0) continue;  // 最后一个顶点

    int v = 0;
    for (auto V : g[u]) {
      if (delFlag[V]) continue;
      v = V;
      break;
    }

    if (nums[u] == 1) {       // 需要进行翻转
      nums[u] = 1 - nums[u];  // 翻转
      nums[v] = 1 - nums[v];  // 翻转
      ans++;
    }
    // 删除点 u
    delFlag[u] = 1;
    childNums[u]--;
    childNums[v]--;
    if (childNums[v] == 1) {
      que.push_back(v);
    }
  }
  return ans;
}

void Solver() {  //

  printf("%d\n", Search());
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