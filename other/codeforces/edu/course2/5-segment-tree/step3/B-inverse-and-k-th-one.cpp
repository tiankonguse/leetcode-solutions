/*
ID: tiankonguse
TASK: B. Inverse and K-th one B. 逆和第 K 个
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/B
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤3 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "B-inverse-and-k-th-one"
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
  vector<ll> sumVal;

  void Init(int n) {
    maxNM = n + 1;
    sumVal.resize(maxNM << 2, 0);
    sign.resize(maxNM << 2, 0);
  }

  void UpdateNode(int rt, int l, int r, ll v) {
    const int num = r - l + 1;
    const int oldSum = sumVal[rt];
    if (sign[rt]) {
      sign[rt] = 0;
      sumVal[rt] = num - oldSum;
    } else {
      sign[rt] = 1;
      sumVal[rt] = num - oldSum;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    // int m = (l + r) >> 1;
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  void PushDown(int rt, int l, int r) {
    if (sign[rt]) {
      int m = (l + r) >> 1;
      UpdateNode(rt << 1, l, m, sign[rt]);
      UpdateNode(rt << 1 | 1, m + 1, r, sign[rt]);

      sign[rt] = 0;
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
    if (L <= m) Update(L, R, add, l, m, rt << 1);
    if (R > m) Update(L, R, add, m + 1, r, rt << 1 | 1);
    PushUp(rt, l, r);
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m && m < R) {
      return QuerySum(L, R, l, m, rt << 1) + QuerySum(L, R, m + 1, r, rt << 1 | 1);
    } else if (m < R) {
      return QuerySum(L, R, m + 1, r, rt << 1 | 1);
    } else {
      return QuerySum(L, R, l, m, rt << 1);
    }
  }
};

int n, m;
void InitIO() {
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
}

SegTree segTree;

int Search(int k) {
  int l = 1, r = n;
  while (l < r) {
    int mid = (l + r) / 2;
    if (segTree.QuerySum(1, mid) < k) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return r;
}

void Solver() {  //
  segTree.Init(n);
  segTree.Build();
  while (m--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int l, r;
      scanf("%d%d", &l, &r);
      segTree.Update(l + 1, r, 1);
      // printf("sum=%lld\n", segTree.QuerySum(1, n));
    } else {
      int k;
      scanf("%d", &k);
      printf("%d\n", Search(k + 1) - 1);
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