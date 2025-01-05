/*
ID: tiankonguse
TASK: E. Wall  E·沃尔
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/E
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
DESC:
  固定 2 个元素，默认为 {INT_MAX, 0}
  与 V6 的区别是，不使用延迟标记，数据自身就是延迟标记
*/
#define TASK "E-wall-v7"
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod_10_9_7 = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(L,R) 3.update(L,R,V)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

int maxNM;

typedef long long ll;

enum { UP = 1, DOWN = 2 };
void Merge(const pair<int, ll>& os, pair<int, ll>& ops) {
  auto& [o3, o4] = os;   // UP,DOWN
  auto& [o1, o2] = ops;  // UP,DOWN

  // o1(up)->o2(down)->o3(up)->o4(down)
  if (o3 == o4) {  // 新值固定
    o1 = o2 = o3;
  } else if (o1 == o2) {
    // TODO: 旧值固定。可能存在贪心反例 - 一分析所有case，不存在反例
    if (o3 > o1) {
      o1 = o2 = o3;
    }
    if (o4 < o1) {
      o1 = o2 = o4;
    }
  } else {
    if (o3 >= o2) {
      o1 = o2 = o3;
    } else if (o4 <= o1) {
      o1 = o2 = o4;
    } else {
      o1 = max(o1, o3);
      o2 = min(o2, o4);
    }
  }
}
struct SegTree {
  vector<pair<int, ll>> signVal;  // 延迟标记 {UP, Down}

  void Init(int n) {
    maxNM = n + 1;
    signVal.resize(maxNM << 2);
  }

  void UpdateNode(int rt, int l, int r, const pair<int, ll>& o) { Merge(o, signVal[rt]); }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
  }
  void PushDown(int rt, int l, int r) {
    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, signVal[rt]);
    UpdateNode(rt << 1 | 1, m + 1, r, signVal[rt]);
    signVal[rt] = {0, INT_MAX};
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    signVal[rt] = {0, 0};
    if (l == r) {
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, const pair<int, ll>& o, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, o);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, o, lson);
    if (R > m) Update(L, R, o, rson);
    PushUp(rt, l, r);
  }
  vector<ll> ans;
  void QuerySum(int n, int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      if (l <= n) {
        ans[l] = signVal[rt].first;
      }
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    QuerySum(n, lson);
    QuerySum(n, rson);
  }
};

int n, m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
}

SegTree segTree;
void Solver() {  //
  segTree.Init(n);
  segTree.Build();
  pair<int, ll> os;
  while (m--) {
    int op;
    int l, r;
    ll d;
    scanf("%d%d%d%lld", &op, &l, &r, &d);

    if (op == UP) {
      os = {d, INT_MAX};
    } else {
      os = {0, d};
    }
    segTree.Update(l + 1, r + 1, os);
  }
  segTree.ans.reserve(n + 1);
  segTree.QuerySum(n);
  for (int i = 1; i <= n; i++) {
    printf("%lld\n", segTree.ans[i]);
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