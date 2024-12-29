/*
ID: tiankonguse
TASK: A. Assignment and Maximal Segment A. 赋值和最大段
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/A
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤3 » 实践
submission:
*/
#define TASK "A-assignment-maximal-segment"
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

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;

struct SegTree {
  vector<bool> sign;
  vector<ll> signVal;
  vector<ll> maxVal;  // 子区间的最优值，至少1个
  vector<ll> preVal;  // 前缀最优值，至少1个
  vector<ll> sufVal;  // 后缀最优值，至少1个
  vector<ll> sumVal;

  void Init(int n) {
    maxNM = n + 1;
    maxVal.resize(maxNM << 2, 0);
    preVal.resize(maxNM << 2, 0);
    sufVal.resize(maxNM << 2, 0);
    sumVal.resize(maxNM << 2, 0);
    signVal.resize(maxNM << 2, 0);
    sign.resize(maxNM << 2, 0);
  }

  ll Op(ll a, ll b) {  //
    return a + b;
  }

  void UpdateNode(int rt, int l, int r, ll v) {
    sign[rt] = 1;
    signVal[rt] = v;
    sumVal[rt] = v * (r - l + 1);
    preVal[rt] = max(0ll, sumVal[rt]);
    sufVal[rt] = max(0ll, sumVal[rt]);
    maxVal[rt] = max(0ll, sumVal[rt]);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    int m = (l + r) >> 1;
    preVal[rt] = max(preVal[rt << 1], sumVal[rt << 1] + preVal[rt << 1 | 1]);
    sufVal[rt] = max(sufVal[rt << 1] + sumVal[rt << 1 | 1], sufVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt], max(preVal[rt], sufVal[rt]));
    maxVal[rt] = max(maxVal[rt], sufVal[rt << 1] + preVal[rt << 1 | 1]);
  }
  void PushDown(int rt, int l, int r) {
    if (sign[rt]) {
      int m = (l + r) >> 1;
      UpdateNode(rt << 1, l, m, signVal[rt]);
      UpdateNode(rt << 1 | 1, m + 1, r, signVal[rt]);

      sign[rt] = 0;
      signVal[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, add);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  tuple<ll, ll, ll, ll> QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return {maxVal[rt], sumVal[rt], preVal[rt], sufVal[rt]};
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m && m < R) {
      auto [leftMax, leftSum, leftPre, leftSuf] = QueryMax(L, R, lson);
      auto [rightMax, rightSum, rightPre, rightSuf] = QueryMax(L, R, rson);

      ll retPre = max(leftPre, leftSum + rightPre);
      ll retSuf = max(leftSuf + rightSum, rightSuf);
      ll 

    } else if (m < R) {
      return QueryMax(L, R, rson);
    } else {
      return QueryMax(L, R, lson);
    }
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
  while (m--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int l, r;
      ll v;
      scanf("%d%d%lld", &l, &r, &v);
      segTree.Update(l + 1, r, v + 1);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", segTree.QueryMin(l + 1, r) - (r - l));
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
  // ll a = mod_10_9_7;
  // printf("a=%lld\n", a * a);
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/