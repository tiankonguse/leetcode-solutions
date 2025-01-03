/*
ID: tiankonguse
TASK: C. Painter  C、画家
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/C
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "C-painter"
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

template <class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_queue = priority_queue<T>;

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
enum { W = 1, B = 2 };

struct Node {
  int sum, num, left, right;
  Node() { sum = num = left = right = 0; }
  void Fill(int v) {
    sum = left = right = v;
    num = v > 0 ? 1 : 0;
  }
};

struct SegTree {
  vector<ll> flag;     // 延迟标记
  vector<Node> opVal;  // 内部 B 的个数

  void Init(int n) {
    maxNM = n + 1;
    flag.resize(maxNM << 2, 0);  // 全部打上延迟标记，都是 W 颜色
    opVal.resize(maxNM << 2);
  }

  void UpdateNode(int rt, int l, int r, int v) {
    flag[rt] = v;
    if (v == B) {
      opVal[rt].Fill(r - l + 1);
    } else {
      opVal[rt].Fill(0);
    }
  }

  void Merge(const Node& L, const Node& R, Node& P, int l, int m, int r) {
    P.sum = L.sum + R.sum;

    if (L.left == m - l + 1) {
      P.left = L.left + R.left;
    } else {
      P.left = L.left;
    }

    if (R.right == r - (m + 1) + 1) {
      P.right = R.right + L.right;
    } else {
      P.right = R.right;
    }

    if (L.right == 0 || R.left == 0) {
      P.num = L.num + R.num;
    } else {
      P.num = L.num + R.num - 1;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    int m = (l + r) / 2;
    Merge(opVal[rt << 1], opVal[rt << 1 | 1], opVal[rt], l, m, r);
  }
  void PushDown(int rt, int l, int r) {
    if (flag[rt] == 0) return;

    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, flag[rt]);
    UpdateNode(rt << 1 | 1, m + 1, r, flag[rt]);
    flag[rt] = 0;
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
  void Update(int L, int R, int v, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, v);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, v, lson);
    if (R > m) Update(L, R, v, rson);
    PushUp(rt, l, r);
  }
  Node QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return opVal[rt];
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (R <= m) {
      return QuerySum(L, R, lson);
    } else if (L > m) {
      return QuerySum(L, R, rson);
    } else {
      Node ret;
      Node leftRet = QuerySum(L, R, lson);
      Node rightRet = QuerySum(L, R, rson);
      Merge(leftRet, rightRet, ret, max(l, L), m, min(r, R));
      return ret;
    }
  }
};

int n;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%d", &n);
}

const int N = 1e6 + 10;
const int N2 = 5e5 + 1;
SegTree segTree;
void Solver() {  //
  segTree.Init(N);
  segTree.Build();
  while (n--) {
    char op[2];
    int x, l;
    scanf("%s%d%d", op, &x, &l);

    int L = x + N2;
    int R = L + l - 1;
    int v = op[0] == 'W' ? W : B;
    segTree.Update(L, R, v);
    Node ret = segTree.QuerySum(1, N);
    printf("%d %d\n", ret.num, ret.sum);
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