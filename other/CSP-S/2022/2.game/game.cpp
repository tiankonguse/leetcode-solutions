/*
ID: tiankonguse
TASK: game
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8818
PATH: P8818 [CSP-S 2022] 策略游戏
submission: https://www.luogu.com.cn/record/220958363
*/
#define TASK "game"
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// #define TASKNO "4"
//   freopen(TASK TASKNO ".in", "r", stdin);
//   freopen(TASK TASKNO ".out", "w", stdout);
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
const ll kMaxVal = 10e9 + 10;
const ll kMinVal = -kMaxVal;

int maxNM;

typedef long long ll;
struct Node {
  // 负数最小值、最大值、正数最小值、最大值、0值
  ll negMin = kMaxVal, negMax = kMinVal, posMin = kMaxVal, posMax = kMinVal, zero = 0;
};
struct SegTree {
  vector<Node> nodes;
  vector<ll> str;

  void Init(const vector<int>& str_, const ll default_val = 0) {
    // maxNM = str_.size() + 1;
    nodes.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }
  Node merge(const Node& left, const Node& right) {
    Node cur;
    cur.negMin = min(left.negMin, right.negMin);
    cur.negMax = max(left.negMax, right.negMax);
    cur.posMin = min(left.posMin, right.posMin);
    cur.posMax = max(left.posMax, right.posMax);
    cur.zero = left.zero + right.zero;
    return cur;
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    nodes[rt] = merge(nodes[rt << 1], nodes[rt << 1 | 1]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      const ll& val = str[l];
      if (val > 0) {
        nodes[rt].posMin = min(nodes[rt].posMin, val);
        nodes[rt].posMax = max(nodes[rt].posMax, val);
      } else if (val < 0) {
        nodes[rt].negMin = min(nodes[rt].negMin, val);
        nodes[rt].negMax = max(nodes[rt].negMax, val);
      } else {
        nodes[rt].zero = 1;
      }
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  Node Query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return nodes[rt];
    }
    int m = (l + r) >> 1;
    Node node;
    if (L <= m) {
      node = merge(node, Query(L, R, lson));
    }
    if (m < R) {
      node = merge(node, Query(L, R, rson));
    }
    return node;
  }
};

int n, m, q;
vector<int> A, B;
SegTree segTreeA, segTreeB;
void Solver() {  //
  scanf("%d%d%d", &n, &m, &q);
  A.resize(n);
  B.resize(m);
  maxNM = max(n, m) + 1;
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &B[i]);
  }
  segTreeA.Init(A);
  segTreeA.Build();
  segTreeB.Init(B);
  segTreeB.Build();
  while (q--) {
    int l1, r1, l2, r2;
    scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
    auto nodeA = segTreeA.Query(l1, r1);
    auto nodeB = segTreeB.Query(l2, r2);
    MyPrintf("nodeA: negMin:%lld negMax:%lld posMin:%lld posMax:%lld zero:%lld\n", nodeA.negMin, nodeA.negMax,
             nodeA.posMin, nodeA.posMax, nodeA.zero);
    MyPrintf("nodeB: negMin:%lld negMax:%lld posMin:%lld posMax:%lld zero:%lld\n", nodeB.negMin, nodeB.negMax,
             nodeB.posMin, nodeB.posMax, nodeB.zero);
    ll ans = 0;
    if (nodeB.posMax > 0 && nodeB.negMin < 0) {
      // 情况1：B 区间有正负，A 需要优先选择 0，其次正负都选择，取最小的
      if (nodeA.zero > 0) {
        ans = 0;
      } else if (nodeA.posMax > 0 && nodeA.negMin < 0) {
        ans = max(nodeA.posMin * nodeB.negMin, nodeA.negMax * nodeB.posMax);
      } else if (nodeA.posMax > 0) {
        ans = nodeA.posMin * nodeB.negMin;
      } else {
        ans = nodeA.negMax * nodeB.posMax;
      }
    } else if (nodeB.posMax > 0) {
      // 情况2：B 区间有正数没负数，A 需要优先选择正数，其次 0，取最大的负数
      if (nodeA.posMax > 0) {
        if (nodeB.zero > 0) {
          ans = 0;
        } else {
          ans = nodeA.posMax * nodeB.posMin;
        }
      } else if (nodeA.zero > 0) {
        ans = 0;
      } else {
        ans = nodeA.negMax * nodeB.posMax;
      }
    } else if (nodeB.negMin < 0) {
      // 情况2：B 区间有负数没正数，A 需要优先选择负数，其次 0，最后最小的正数
      if (nodeA.negMin < 0) {
        if (nodeB.zero > 0) {
          ans = 0;
        } else {
          ans = nodeA.negMin * nodeB.negMax;
        }
      } else if (nodeA.zero > 0) {
        ans = 0;
      } else {
        ans = nodeA.posMin * nodeB.negMin;
      }
    } else {
      ans = 0;
    }
    printf("%lld\n", ans);
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