/*
ID: tiankonguse
TASK: C. Assignment to Segment  C. 分配给段
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤1 » 实践
submission: https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/submission/298746340
*/
#define TASK "C-assignment-to-segment"
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
  vector<ll> sign;
  vector<ll> minVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sign.resize(maxNM << 2, 0);
    minVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] = sign[rt];
      minVal[rt << 1] = sign[rt];

      sign[rt << 1 | 1] = sign[rt];
      minVal[rt << 1 | 1] = sign[rt];
      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      minVal[rt] = 1;
      return;
    }
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = add;
      minVal[rt] = add;
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, l, m, rt << 1);
    if (R > m) Update(L, R, add, m + 1, r, rt << 1 | 1);
    PushUp(rt, l, r);
  }
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = INT_MAX;  // 求最小值，初始值设置为最大值
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, l, m, rt << 1));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, m + 1, r, rt << 1 | 1));
    }
    return ret;
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
      int l, r, v;
      scanf("%d%d%d", &l, &r, &v);
      segTree.Update(l + 1, r, v + 1);
    } else {
      int i;
      scanf("%d", &i);
      printf("%lld\n", segTree.QueryMin(i + 1, i + 1) - 1);
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
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
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