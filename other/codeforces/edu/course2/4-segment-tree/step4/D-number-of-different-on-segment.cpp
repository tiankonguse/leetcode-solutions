/*
ID: tiankonguse
TASK: D. Number of Different on Segment D. 段上不同的数量
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/D
PATH: ITMO 学院：试点课程 » 线段树，第 1 部分 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/submission/298742800
*/
#define TASK "D-number-of-different-on-segment"
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
const int kMaxVal = 10e8;

int maxNM;

const int N = 41;
struct Matrix {
 public:
  int mat[N];
  ll num;
  int val;
  Matrix() {
    num = 0;
    val = 0;
    memset(mat, 0, sizeof(mat));
  }
  void Set(int p) {
    if (mat[val] == 1) {
      mat[val] = 0;
    }
    num = 1;
    val = p;
    mat[p] = 1;
  }
};

void Merge(const Matrix& a, const Matrix& b, Matrix& c) {
  c.mat[0] = 0;
  c.num = 0;
  for (int i = 1; i < N; i++) {
    c.mat[i] = a.mat[i] | b.mat[i];
    c.num += c.mat[i];
  }
}
typedef long long ll;
struct SegTree {
  vector<Matrix> sumVal;
  vector<int> str;

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    sumVal.resize(maxNM << 2);
    str.clear();
    str.resize(maxNM + 1, default_val);
    for (size_t i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    Merge(sumVal[rt << 1], sumVal[rt << 1 | 1], sumVal[rt]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt].Set(str[l]);  // 单点更新
      return;
    }
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(rt, l, r);
  }
  void Update(int L, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      sumVal[rt].Set(add);  // 单点更新
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, l, m, rt << 1);
    if (L > m) Update(L, add, m + 1, r, rt << 1 | 1);
    PushUp(rt, l, r);
  }
  Matrix QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    int m = (l + r) >> 1;
    Matrix ret;
    if (L <= m && m < R) {  // 左右都有
      Matrix a = QuerySum(L, R, l, m, rt << 1);
      Matrix b = QuerySum(L, R, m + 1, r, rt << 1 | 1);
      Merge(a, b, ret);
    } else if (m < R) {
      ret = QuerySum(L, R, m + 1, r, rt << 1 | 1);
    } else if (L <= m) {
      ret = QuerySum(L, R, l, m, rt << 1);
    }
    return ret;
  }
};

int n, m;
vector<int> nums;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
}

SegTree segTree;
void Solver() {  //
  segTree.Init(nums);
  segTree.Build();
  while (m--) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      printf("%lld\n", segTree.QuerySum(x, y).num);
    } else {
      segTree.Update(x, y);
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