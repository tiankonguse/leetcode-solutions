/*
ID: tiankonguse
TASK: T549580 【MX-X7-T3】[LSOT-3] 寄存器
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/T561109?contestId=218816
PATH:
submission: https://github.com/tiankonguse/leetcode-solutions/
*/
#define TASK "B-v2"
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
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  g.resize(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

vector<vector<int>> dp;

/*
  flag=0 父节点没有通电
  flag=1 父节点通电
*/
int Dfs(const int u, const int flag, const int pre) {
  int& ret = dp[u][flag];
  if (ret != -1) return ret;

  ret = 0;
  if (nums[u]) {  // 当前节点
    if (flag) {
      for (auto v : g[u]) {
        if (v == pre) continue;
        ret += min(Dfs(v, 0, u), Dfs(v, 1, u));
      }
    } else {
      ret += 1;  // 需要通电，但是没电，当前节点需要额外通电
      for (const auto v : g[u]) {
        if (v == pre) continue;
        ret += min(Dfs(v, 0, u), Dfs(v, 1, u));
      }
    }
  } else {
    if (flag) {
      ret += 1;
      for (auto v : g[u]) {
        if (v == pre) continue;
        ret += min(Dfs(v, 0, u), Dfs(v, 1, u));
      }
    } else {
      for (auto v : g[u]) {
        if (v == pre) continue;
        ret += Dfs(v, 0, u);  // 没电，儿子独立更生
      }
    }
  }
  return ret;
}

void Solver() {  //
  dp.resize(n, vector<int>(2, -1));
  printf("%d\n", Dfs(0, 0, -1));
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("USACO my 用时: %.0lfms\n", my.count());
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