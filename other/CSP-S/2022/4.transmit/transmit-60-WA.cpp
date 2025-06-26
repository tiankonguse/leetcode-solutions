/*
ID: tiankonguse
TASK: transmit
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8820
PATH: P8820 [CSP-S 2022] 数据传输
submission: https://www.luogu.com.cn/record/221304194
评测分数:
*/
#define TASK "transmit"
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

enum { K_L_2 = 0, K_L_1, K_0, K_R_1, K_R_2, K_SON, K_MAX };
const int maxn = 200015;
const int maxn_log = 20;  // 17.6096765414
vector<int> g[maxn];      // 有向树
ll f[maxn][maxn_log][K_MAX], dep[maxn], minChild[maxn], minChildIndex[maxn];
ll F[maxn][maxn_log][K_MAX];  // 区间最小路径和
ll costSum[maxn] = {0};
vector<int> G[maxn];  // 无向树
ll costs[maxn] = {0};
int n, Q, k;

void DfsRMQ(const int u) {
  for (const int v : g[u]) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    dep[v] = dep[u] + 1;

    f[v][0][K_L_2] = v;  // 父节点的孙子非法， 递归禁止使用 K_L_2
    f[v][0][K_L_1] = v;  // 父节点的儿子是自己
    f[v][0][K_0] = u;
    f[v][0][K_R_1] = f[u][0][K_0];  // 父节点的父节点
    f[v][0][K_R_2] = f[u][1][K_0];  // 父节点的父节点
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
    for (int i = 1; i < maxn_log; i++) {
      f[v][i][K_L_2] = f[f[v][i - 1][K_L_1]][i - 1][K_L_1];
      f[v][i][K_L_1] = f[f[v][i - 1][K_0]][i - 1][K_L_1];
      f[v][i][K_0] = f[f[v][i - 1][K_0]][i - 1][K_0];
      f[v][i][K_R_1] = f[f[v][i - 1][K_0]][i - 1][K_R_1];
      f[v][i][K_R_2] = f[f[v][i - 1][K_0]][i - 1][K_R_2];
    }

    if (k == 2) {
      F[v][0][K_L_1] = 0;                      // 自己
      F[v][0][K_0] = costs[f[v][0][K_0]];      // 一层父节点，一步到位
      F[v][0][K_R_1] = costs[f[v][0][K_R_1]];  // 二层父节点，一步到位
      for (int i = 1; i < maxn_log; i++) {
        F[v][i][K_L_1] = min(F[v][i - 1][K_L_1] + F[f[v][i - 1][K_L_1]][i - 1][K_0],  //
                             F[v][i - 1][K_0] + F[f[v][i - 1][K_0]][i - 1][K_L_1]);
        F[v][i][K_0] = min(F[v][i - 1][K_0] + F[f[v][i - 1][K_0]][i - 1][K_0],  //
                           F[v][i - 1][K_L_1] + F[f[v][i - 1][K_L_1]][i - 1][K_R_1]);
        F[v][i][K_R_1] = min(F[v][i - 1][K_0] + F[f[v][i - 1][K_0]][i - 1][K_R_1],  //
                             F[v][i - 1][K_R_1] + F[f[v][i - 1][K_R_1]][i - 1][K_0]);
      }
    } else if (k == 3) {
      // v -> fa
      F[v][0][K_L_2] = 0;                       // 非法
      F[v][0][K_L_1] = 0;                       // 自己
      F[v][0][K_0] = costs[f[v][0][K_0]];       // 一层父节点，一步到位
      F[v][0][K_R_1] = costs[f[v][0][K_R_1]];   // 二层父节点，一步到位
      F[v][0][K_R_2] = costs[f[v][0][K_R_2]];   // 三层父节点，一步到位
      F[v][0][K_SON] = minChild[f[v][0][K_0]];  // 一层父亲的儿子，一步到位

      F[v][1][K_L_2] = 0;                       // 自己
      F[v][1][K_L_1] = costs[f[v][1][K_L_1]];   // 一层父节点，一步到位
      F[v][1][K_0] = costs[f[v][1][K_0]];       // 二层父节点，一步到位
      F[v][1][K_R_1] = costs[f[v][1][K_R_1]];   // 三层父节点，一步到位
      F[v][1][K_SON] = minChild[f[v][1][K_0]];  // 二层父亲的儿子，一步到位
      F[v][1][K_R_2] = costs[f[v][1][K_R_2]] + min({
                                                   F[v][1][K_L_1],  // 一层父节点
                                                   F[v][1][K_0],    // 二层父节点
                                                   F[v][1][K_R_1],  // 三层父节点
                                                   F[v][1][K_SON]   // 二层父亲的儿子
                                               });                  // 四层父节点

      F[v][2][K_L_2] = F[v][1][K_0];    // 二层父节点,一步到位
      F[v][2][K_L_1] = F[v][1][K_R_1];  // 三层父节点,一步到位
      F[v][2][K_0] = F[v][1][K_R_2];    // 四层父节点， 2^2 = 2^1+2
      F[v][2][K_SON] = minChild[f[v][2][K_0]] + min({
                                                    F[v][2][K_0],              // 四层父节点
                                                    F[v][2][K_L_1],            // 三层父节点
                                                    F[v][2][K_L_2],            // 两层父节点
                                                    F[f[v][1][K_0]][0][K_SON]  // 三层父节点的最小儿子
                                                });
      F[v][2][K_R_1] = costs[f[v][2][K_R_1]] + min({
                                                   F[v][2][K_0],               // 四层父节点
                                                   F[v][2][K_SON],             // 四层父节点的最小儿子
                                                   F[v][2][K_L_1],             // 三层父节点
                                                   F[f[v][1][K_0]][0][K_SON],  // 三层父节点的最小儿子
                                                   F[v][2][K_L_2],             // 两层父节点
                                               });

      F[v][2][K_R_2] = costs[f[v][2][K_R_2]] + min({
                                                   F[v][2][K_R_1],             // 五层父节点
                                                   F[f[v][2][K_0]][0][K_SON],  // 五层父节点的最小儿子
                                                   F[v][2][K_0],               // 四层父节点
                                                   F[v][2][K_SON],             // 四层父节点的最小儿子
                                                   F[v][2][K_L_1],             // 三层父节点
                                               });

      // v->fa->fa
      for (int i = 3; i < maxn_log; i++) {
        // i-1:  v->fa1(K_L_1)->fa2(K_0)->fa3(K_R_1)->fa4
        // i:    v->fa1       ->fa2     ->fa3(K_L_1)->fa4(K_0)->fa5(K_R_1)
        // int fa_l_1 = f[v][i - 1][K_L_1];
        int fa_l_2 = f[v][i - 1][K_L_2];
        int fa_l_1 = f[v][i - 1][K_L_1];
        int fa_0 = f[v][i - 1][K_0];
        int fa_r_1 = f[v][i - 1][K_R_1];
        int fa_r_2 = f[fa_r_1][0][K_0];

        F[v][i][K_L_2] = min({
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_L_2],      //
            F[v][i - 1][K_SON] + F[fa_l_1][i - 1][K_L_1],  //
            F[v][i - 1][K_L_1] + F[fa_l_1][i - 1][K_L_1],  //
            F[v][i - 1][K_L_2] + F[fa_l_2][i - 1][K_0]     //
        });
        F[v][i][K_L_1] = min({
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_L_1],     //
            F[v][i - 1][K_SON] + F[fa_l_1][i - 1][K_0],   //
            F[v][i - 1][K_L_1] + F[fa_l_1][i - 1][K_0],   //
            F[v][i - 1][K_R_1] + F[fa_r_1][i - 1][K_L_2]  //
        });
        F[v][i][K_0] = min({
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_0],        //
            F[v][i - 1][K_SON] + F[fa_l_1][i - 1][K_R_1],  //
            F[v][i - 1][K_L_1] + F[fa_l_1][i - 1][K_R_1],  //
            F[v][i - 1][K_R_1] + F[fa_r_1][i - 1][K_L_1],  //
        });
        F[v][i][K_SON] = min({
            F[v][i][K_L_2] + costs[f[v][i][K_0]],
            F[v][i][K_L_1] + costs[f[v][i][K_0]],
            F[v][i][K_0] + costs[f[v][i][K_0]],
            F[v][i - 1][K_L_1] + F[fa_l_1][i - 1][K_SON] + costs[f[v][i][K_0]],
            F[v][i - 1][K_SON] + F[fa_l_1][i - 1][K_SON] + costs[f[v][i][K_0]],
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_SON],
        });

        F[v][i][K_R_1] = min({
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_R_1],      //
            F[v][i - 1][K_SON] + F[fa_l_1][i - 1][K_R_2],  //
            F[v][i - 1][K_L_1] + F[fa_l_1][i - 1][K_R_2],  //
            F[v][i - 1][K_R_1] + F[fa_r_1][i - 1][K_0],    //
        });
        F[v][i][K_R_2] = min({
            F[v][i - 1][K_0] + F[fa_0][i - 1][K_R_2],      //
            F[v][i - 1][K_R_1] + F[fa_r_1][i - 1][K_R_1],  //
            F[v][i - 1][K_R_2] + F[fa_r_2][i - 1][K_0],    //
            F[v][i][K_R_1] + costs[f[v][i][K_R_2]],        // 一层父节点
            F[v][i][K_0] + costs[f[v][i][K_R_2]],          // 二层父节点
            F[v][i][K_L_1] + costs[f[v][i][K_R_2]],        // 三层父节点
            F[v][i][K_SON] + costs[f[v][i][K_R_2]],        // 三层父节点
        });
      }
    }
    DfsRMQ(v);
  }
}

void DfsInit(int u, int fa) {
  minChild[u] = 1e10;
  minChildIndex[u] = -1;
  for (int v : G[u]) {
    if (v == fa) continue;
    g[u].push_back(v);
    DfsInit(v, u);
    if (minChild[u] > costs[v]) {
      minChild[u] = costs[v];
      minChildIndex[u] = v;
    }
  }
}

// u 向上跳 k 步，返回跳到的节点编号
int PreKthAncestor(int u, int k) {
  for (int i = maxn_log - 1; k && i >= 0; i--) {
    if (k & (1 << i)) {
      u = f[u][i][K_0];
      k = k ^ (1 << i);
    }
  }
  return u;
}
void DfsCost(int u) {
  for (int v : g[u]) {
    costSum[v] = costSum[u] + costs[v];
    for (int i = 1; i <= k; i++) {
      // f(v) = min(f(u), f(fa(u)), f(fa(fa(u))), ...) + costs[v] 选择前 k 个祖先的最小值
      costSum[v] = min(costSum[v], costSum[PreKthAncestor(v, i)] + costs[v]);
    }
    DfsCost(v);
  }
}

const int kHead = 10;
void Init() {
  DfsInit(1 + kHead, -1);
  for (int i = 0; i <= kHead; i++) {
    g[i].push_back(i + 1);
    minChild[i] = costs[i + 1];
    minChildIndex[i] = i + 1;
  }
  memset(f, 0, sizeof f);
  memset(F, 0, sizeof F);
  DfsRMQ(0);
  memset(costSum, 0, sizeof costSum);
  DfsCost(0);
}

int Lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
    if (d & (1 << i)) {
      u = f[u][i][K_0];
      d = d ^ (1 << i);
    }
  }
  if (u == v) return u;
  for (int i = maxn_log - 1; i >= 0; i--) {
    if (f[u][i][K_0] != f[v][i][K_0]) {
      u = f[u][i][K_0];
      v = f[v][i][K_0];
    }
  }
  return f[u][0][K_0];
}

int PathDepSum(int u, int v) {
  int lca = Lca(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}
ll PathCostSum(int u, int v) {
  int lca = Lca(u, v);
  return costSum[u] + costSum[v] - 2 * costSum[lca] + costs[lca];
}

void Check2() {
  for (int u = 1 + kHead; u <= n + kHead; u++) {
    MyAssert(F[u][0][K_L_1] == 0);
    MyAssert(F[u][0][K_0] == F[u][1][K_L_1]);    // 2^0 = 2^1 - 1
    MyAssert(F[u][0][K_R_1] == F[u][1][K_0]);    // 2^0 + 1 == 2^2
    MyAssert(F[u][1][K_L_1] == F[u][0][K_0]);    // 2^1 - 1 = 2^0
    MyAssert(F[u][1][K_0] == F[u][0][K_R_1]);    // 2^1 = 2^1 + 1
    MyAssert(F[u][1][K_R_1] == F[u][2][K_L_1]);  // 2^1 + 1 = 2^2-1
    MyAssert(F[u][0][K_0] == costs[PreKthAncestor(u, 1)]);
    MyAssert(F[u][0][K_R_1] == costs[PreKthAncestor(u, 2)]);
    MyAssert(F[u][1][K_0] == costs[PreKthAncestor(u, 2)]);
    MyAssert(F[u][1][K_L_1] == costs[PreKthAncestor(u, 1)]);
  }
}

ll PathCostPreKth2(const int u, int k) {  //
  if (k == 0) return 0;
  if (k == 1) return F[u][0][K_0];
  if (k == 2) return F[u][1][K_0];
  if (k == 3) return F[u][1][K_R_1];
  if (k == 4) return F[u][2][K_0];
  // u,u+1 -> u+2^i,u+1+2^i
  ll ans_l_1 = 0;
  ll ans_0 = 0;
  int u_0 = u;
  int u_l_1 = u;
  int firstFlag = true;
  for (int i = maxn_log - 1; k && i >= 0; i--) {
    if (k == 1) {
      return min({ans_l_1, ans_0}) + F[u_0][0][K_0];
    }
    if (k & (1 << i)) {
      if (firstFlag) {
        firstFlag = false;
        ans_l_1 = F[u][i][K_L_1];
        ans_0 = F[u][i][K_0];
        u_0 = f[u][i][K_0];
        u_l_1 = f[u][i][K_L_1];
        k = k ^ (1 << i);
      } else {
        ll tmp_ans_l_1 = min(ans_l_1 + F[u_l_1][i][K_0], ans_0 + F[u_0][i][K_L_1]);
        ll tmp_ans_0 = min(ans_0 + F[u_0][i][K_0], ans_l_1 + F[u_l_1][i][K_R_1]);
        ans_l_1 = tmp_ans_l_1;
        ans_0 = tmp_ans_0;
        u_0 = f[u_0][i][K_0];
        u_l_1 = f[u_l_1][i][K_0];
        k = k ^ (1 << i);
      }
    }
  }
  return ans_0;
}

void Check3() {
  for (int u = 1 + kHead; u <= n + kHead; u++) {
    MyAssert(F[u][0][K_L_1] == 0);
    MyAssert(F[u][0][K_0] == F[u][1][K_L_1]);    // 2^0 = 2^1 - 1
    MyAssert(F[u][0][K_R_1] == F[u][1][K_0]);    // 2^0 + 1 == 2^2
    MyAssert(F[u][1][K_L_1] == F[u][0][K_0]);    // 2^1 - 1 = 2^0
    MyAssert(F[u][1][K_0] == F[u][0][K_R_1]);    // 2^1 = 2^1 + 1
    MyAssert(F[u][1][K_R_1] == F[u][2][K_L_1]);  // 2^1 + 1 = 2^2-1
    MyAssert(F[u][0][K_0] == costs[PreKthAncestor(u, 1)]);
    MyAssert(F[u][0][K_R_1] == costs[PreKthAncestor(u, 2)]);
    MyAssert(F[u][1][K_0] == costs[PreKthAncestor(u, 2)]);
    MyAssert(F[u][1][K_L_1] == costs[PreKthAncestor(u, 1)]);
  }
}
ll PathCostPreKth3(const int U, int k) {
  if (k == 0) return 0;
  if (k == 1) return F[U][0][K_0];
  if (k == 2) return F[U][1][K_0];
  if (k == 3) return F[U][1][K_R_1];
  if (k == 4) return F[U][2][K_0];
  ll ans_l_2 = 0;
  ll ans_l_1 = 0;
  ll ans_0 = 0;
  ll ans_son = 0;
  ll ans_r_1 = 0;
  ll ans_r_2 = 0;
  int u_0 = U;
  int u_l_1 = U;
  int u_l_2 = U;
  int u_r_1 = U;
  int u_r_2 = U;
  int firstFlag = true;
  for (int i = maxn_log - 1; k && i >= 0; i--) {
    if (k == 1) {
      return min({ans_l_2, ans_l_1, ans_0}) + F[u_0][0][K_0];
    } else if (k & (1 << i)) {
      if (firstFlag) {
        firstFlag = false;
        ans_0 = F[U][i][K_0];
        ans_son = F[U][i][K_SON];
        ans_l_1 = F[U][i][K_L_1];
        ans_l_2 = F[U][i][K_L_2];
        ans_r_1 = F[U][i][K_R_1];
        ans_r_2 = F[U][i][K_R_2];
        u_0 = f[U][i][K_0];
        u_l_1 = f[U][i][K_L_1];
        u_l_2 = f[U][i][K_L_2];
        u_r_1 = f[U][i][K_R_1];
        u_r_2 = f[U][i][K_R_2];
        k = k ^ (1 << i);
      } else {
        ll tmp_ans_l_2 = min({
            ans_l_2 + F[u_l_2][i][K_0],    //
            ans_l_1 + F[u_l_1][i][K_L_1],  //
            ans_son + F[u_l_1][i][K_L_1],  //
            ans_0 + F[u_0][i][K_L_2],
        });
        ll tmp_ans_l_1 = min({
            ans_l_2 + F[u_l_2][i][K_R_1],  //
            ans_l_1 + F[u_l_1][i][K_0],    //
            ans_son + F[u_l_1][i][K_0],    //
            ans_0 + F[u_0][i][K_L_1],      //
            ans_r_1 + F[u_r_1][i][K_L_2],  //
        });
        ll tmp_ans_0 = min({
            ans_l_2 + F[u_l_2][i][K_R_2],  //
            ans_l_1 + F[u_l_1][i][K_R_1],  //
            ans_son + F[u_l_1][i][K_R_1],  //
            ans_0 + F[u_0][i][K_0],        //
            ans_r_1 + F[u_r_1][i][K_L_1],  //
            ans_r_2 + F[u_r_2][i][K_L_2],  //
        });
        ll tmp_ans_son = min({
            ans_0 + F[u_0][i][K_SON],                //
            tmp_ans_0 + minChild[f[u_0][i][K_0]],    //
            tmp_ans_l_1 + minChild[f[u_0][i][K_0]],  //
            tmp_ans_l_2 + minChild[f[u_0][i][K_0]],  //
        });
        ll tmp_ans_r_1 = min({
            ans_l_1 + F[u_l_1][i][K_R_2],           //
            ans_son + F[u_l_1][i][K_R_2],           //
            ans_0 + F[u_0][i][K_R_1],               //
            ans_r_1 + F[u_r_1][i][K_0],             //
            ans_r_2 + F[u_r_2][i][K_L_1],           //
            tmp_ans_0 + costs[f[u_0][i][K_R_1]],    //
            tmp_ans_l_1 + costs[f[u_0][i][K_R_1]],  //
            tmp_ans_son + costs[f[u_0][i][K_R_1]],  //
            tmp_ans_l_2 + costs[f[u_0][i][K_R_1]],  //
        });
        ll tmp_ans_r_2 = min({
            ans_0 + F[u_0][i][K_R_2],               //
            ans_r_1 + F[u_r_1][i][K_R_1],           //
            ans_r_2 + F[u_r_2][i][K_0],             //
            tmp_ans_r_1 + costs[f[u_0][i][K_R_2]],  //
            tmp_ans_0 + costs[f[u_0][i][K_R_2]],    //
            tmp_ans_l_1 + costs[f[u_0][i][K_R_2]],  //
            tmp_ans_son + costs[f[u_0][i][K_R_2]],  //
        });
        ans_l_2 = tmp_ans_l_2;
        ans_l_1 = tmp_ans_l_1;
        ans_0 = tmp_ans_0;
        ans_son = tmp_ans_son;
        ans_r_1 = tmp_ans_r_1;
        ans_r_2 = tmp_ans_r_2;
        u_0 = f[u_0][i][K_0];
        u_l_1 = f[u_l_1][i][K_0];
        u_l_2 = f[u_l_2][i][K_0];
        u_r_1 = f[u_r_1][i][K_0];
        u_r_2 = f[u_r_2][i][K_0];
        k = k ^ (1 << i);
      }
    }
  }
  return ans_0;
}

ll PathCostSum2(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);  // 保障 u 是深度更深的, 即 v 可能是 lca
  }
  int lca = Lca(u, v);
  if (v == lca) {
    return costs[u] + PathCostPreKth2(u, dep[u] - dep[lca]);
  }
  // u -> lca -> v
  // u -> u_lca-1 -> v_lca-1, v
  ll ans1 = PathCostPreKth2(u, dep[u] - dep[lca]) + PathCostPreKth2(v, dep[v] - dep[lca]) - costs[lca];
  ll ans2 = PathCostPreKth2(u, dep[u] - dep[lca] - 1) + PathCostPreKth2(v, dep[v] - dep[lca] - 1);
  return min(ans1, ans2) + costs[u] + costs[v];
}
ll PathCostSum3(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);  // 保障 u 是深度更深的, 即 v 可能是 lca
  }
  int lca = Lca(u, v);
  if (v == lca) {
    return costs[u] + PathCostPreKth3(u, dep[u] - dep[lca]);
  }
  MyPrintf("u=%d,v=%d dep[u]=%lld dep[v]=%lld lca=%d dep[lca]=%lld\n", u - kHead, v - kHead, dep[u], dep[v],
           lca - kHead, dep[lca]);
  // u -> lca -> v
  // u -> u_lca-1 -> v_lca-1 -> v
  // u -> u_lca-2 -> v_lca-1 -> v
  // u -> u_lca-1 -> v_lca-2 -> v
  int dep_u = dep[u] - dep[lca];
  int dep_v = dep[v] - dep[lca];
  if (dep_u + dep_v <= 3) {
    return costs[u] + costs[v];  // 一步到位
  }
  ll ans = PathCostPreKth3(u, dep[u] - dep[lca]) + PathCostPreKth3(v, dep[v] - dep[lca]) - costs[lca];
  if(v == 1){
    ll tmp = PathCostPreKth3(u, dep[u] - dep[lca]);
  }
  if (dep_v > 1) {
    int c = minChildIndex[lca];
    ll tmp = PathCostSum3(u, c) - costs[u] + PathCostSum3(c, v) - costs[v] - costs[c];
    ans = min(ans, tmp);
  }
  if (dep_v > 2) {
    int cp = PreKthAncestor(v, dep_v - 1);
    int c = minChildIndex[cp];
    ll tmp = PathCostSum3(u, c) - costs[u] + PathCostSum3(c, v) - costs[v] - costs[c];
    ans = min(ans, tmp);
  }
  if (dep_u > 2) {
    int cp = PreKthAncestor(u, dep_u - 1);
    int c = minChildIndex[cp];
    ll tmp = PathCostSum3(u, c) - costs[u] + PathCostSum3(c, v) - costs[v] - costs[c];
    ans = min(ans, tmp);
  }
  for (int i = 1; i <= 2 && i <= dep_u; i++) {
    for (int j = 1; j <= 2 && j <= dep_v; j++) {
      if (i + j > 3) continue;
      ll tmp = PathCostPreKth3(u, dep[u] - dep[lca] - i) + PathCostPreKth3(v, dep[v] - dep[lca] - j);
      ans = min(ans, tmp);
    }
  }
  return ans + costs[u] + costs[v];
}

vector<tuple<ll, ll, ll>> data3;

void parseData() {
  sort(data3.begin(), data3.end());  // val 排序
  ll base = 1;
  for (int i = 0; i < n; i++) {
    auto& [val, index, newVal] = data3[i];
    newVal = base;
    base *= 10;
  }
  sort(data3.begin(), data3.end(),
       [](const tuple<ll, ll, ll>& a, const tuple<ll, ll, ll>& b) { return get<1>(a) < get<1>(b); });
  for (int i = 0; i < n; i++) {
    printf("%lld ", get<2>(data3[i]));
  }
  printf("\n");
  exit(0);
}

void Solver() {  //
  scanf("%d%d%d", &n, &Q, &k);
  for (int i = 0; i <= kHead; i++) {
    costs[i] = 0;
  }
  for (int i = 1 + kHead; i <= n + kHead; i++) {
    scanf("%lld", &costs[i]);
    MyPrintf("costs[%d]=%lld\n", i - kHead, costs[i]);
    // data3.push_back({costs[i], i, 0});
  }
  // parseData();
  for (int i = 1 + kHead; i < n + kHead; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u += kHead;
    v += kHead;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  Init();
  Check3();
  while (Q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    u += kHead;
    v += kHead;
    if (k == 1) {
      printf("%lld\n", PathCostSum(u, v));
    } else if (k == 2) {
      printf("%lld\n", PathCostSum2(u, v));
    } else {
      MyPrintf("u=%d,v=%d\n", u - kHead, v - kHead);
      printf("%lld\n", PathCostSum3(u, v));
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