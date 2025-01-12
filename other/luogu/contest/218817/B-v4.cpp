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

struct Dsu {
  vector<int> pre;

  void Init(int n) {
    pre.resize(n + 1, 0);
    for (int i = 0; i <= n; i++) {
      pre[i] = i;
    }
  }
  int Get(int u) {
    while (pre[u] != u) {
      u = pre[u] = Get(pre[u]);
    }
    return pre[u];
  }
  void Union(int u, int v) {
    u = Get(u);
    v = Get(v);
    if (u != v) {
      pre[v] = pre[u];
    }
  }
};
Dsu dsu;

ll n;
vector<ll> nums;
vector<set<ll>> gg;
vector<set<ll>> g2;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%lld", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  gg.resize(n);
  for (int i = 1; i < n; i++) {
    ll u, v;
    scanf("%lld%lld", &u, &v);
    u--, v--;
    gg[u].insert(v);
    gg[v].insert(u);
  }
}

vector<vector<ll>> dp;

inline ll Mymin(ll a, ll b, ll c = INT_MAX, ll d = INT_MAX) {  //
  return min(min(c, d), min(a, b));
}

/*
  flag=0 父节点没有通电
  flag=1 父节点通电
*/
ll Dfs(const ll u, const ll flag, const ll pre) {
  if (dp[u][flag] != -1) return dp[u][flag];

  if (nums[u]) {  // 当前节点
    if (flag == 0) {
      ll ans1 = 1;  // 需要通电，但是没电，当前节点需要额外通电
      for (const auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += min(Dfs(v, 0, u), Dfs(v, 1, u));
      }

      ll ans2 = 3;
      for (const auto v : g2[u]) {
        if (v == pre) continue;
        ans2 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = min(ans1, ans2);
    } else if (flag == 1) {
      ll ans1 = 0;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += min(Dfs(v, 0, u), Dfs(v, 1, u));
      }

      ll ans2 = 2;
      for (const auto v : g2[u]) {
        if (v == pre) continue;
        ans2 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = min(ans1, ans2);

    } else if (flag == 2) {
      ll ans1 = 1;  // 需要通电，但是没电，当前节点需要额外通电
      for (const auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = ans1;
    } else {
      ll ans1 = 0;  // 需要通电，但是没电，当前节点需要额外通电
      for (const auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = ans1;
    }
  } else {
    if (flag == 0) {
      ll ans1 = 0;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Dfs(v, 0, u);  // 没电，儿子独立更生
      }

      ll ans2 = 2;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans2 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u));
      }

      ll ans3 = 4;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans3 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = Mymin(ans1, ans2, ans3);
    } else if (flag == 1) {
      ll ans1 = 1;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u));
      }

      ll ans2 = 3;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans2 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }

      return dp[u][flag] = min(ans1, ans2);
    } else if (flag == 2) {
      ll ans1 = 0;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u));
      }

      ll ans2 = 2;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans2 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }

      return dp[u][flag] = min(ans1, ans2);
    } else {
      ll ans1 = 1;
      for (auto v : g2[u]) {
        if (v == pre) continue;
        ans1 += Mymin(Dfs(v, 0, u), Dfs(v, 1, u), Dfs(v, 2, u), Dfs(v, 3, u));
      }
      return dp[u][flag] = ans1;
    }
  }
}

vector<int> maxR;
vector<int> maxH;

int DfsH(int u, int pre) {
  int ans = 0;
  for (auto v : g2[u]) {
    if (v == pre) continue;
    if (nums[u] == 1) {
      if (nums[v] == 1) {
        ans = max(ans, DfsH(v, u));
      } else {
        ans = max(ans, DfsH(v, u) + 1);
      }
    } else {
      ans = max(ans, DfsH(v, u));
    }
  }
  return maxH[u] = ans;
}

vector<vector<int>> maxChilds;
void DfsR(int u, int pre, int preH) {
  vector<int>& maxChild = maxChilds[u];
  auto Add = [&maxChild](int h) {
    if (maxChild.back() < h) {
      maxChild.pop_back();
      maxChild.push_back(h);
      if (maxChild[0] < maxChild[1]) {
        swap(maxChild[0], maxChild[1]);
      }
    }
  };
  Add(preH);
  for (auto v : g2[u]) {
    if (v == pre) continue;
    Add(maxH[v]);
  }
  maxR[u] = maxChild[0] + nums[u];

  for (auto v : g2[u]) {
    if (v == pre) continue;
    int childPreH = maxChild[0];
    if (maxH[v] == maxChild[0]) {
      childPreH = maxChild[1];
    }
    DfsR(v, u, nums[u] + childPreH);
  }
}

void DfsMerge(int u, int pre) {
  if (nums[u] == nums[pre]) {  // 需要合并到 root
    dsu.Union(pre, u);
  }
  for (auto v : gg[u]) {
    if (v == pre) continue;
    DfsMerge(v, u);
  }
}

void DfsG2(int u, int pre) {
  if (nums[u] != nums[pre]) {
    int uu = dsu.Get(u);
    int pp = dsu.Get(pre);
    g2[uu].insert(pp);
  }
  for (auto v : gg[u]) {
    if (v == pre) continue;
    DfsG2(v, u);
  }
}

ll Search() {
  dsu.Init(n);
  DfsMerge(0, 0);
  g2.resize(n);
  DfsG2(0, 0);

  dp.resize(n, vector<ll>(5, -1));
  maxChilds.resize(n, vector<int>(2, 0));
  maxH.resize(n, -1);
  maxR.resize(n, -1);
  DfsH(0, -1);
  DfsR(0, -1, 0);
  int ans = Dfs(0, 0, -1);
  if (ans <= 2) return ans;

  for (int i = 0; i < n; i++) {
    int ii = dsu.Get(i);
    if (i != ii) continue;
    vector<int>& maxChild = maxChilds[i];
    printf("i=%d maxR[i]=%d maxChild=[%d,%d]\n", i, maxR[i], maxChild[0], maxChild[1]);
    if (nums[i]) {
      if (maxChild[0] == maxChild[1]) {
        ans = min(ans, maxR[i] * 2 - 1);
      } else {
        ans = min(ans, maxR[i] * 2 - 2);
      }

    } else {
      if (maxChild[0] == maxChild[1]) {
        ans = min(ans, maxR[i] * 2);
      } else {
        ans = min(ans, maxR[i] * 2 - 1);
      }
    }
  }
  return ans;
}

void Solver() {  //

  printf("%lld\n", Search());
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