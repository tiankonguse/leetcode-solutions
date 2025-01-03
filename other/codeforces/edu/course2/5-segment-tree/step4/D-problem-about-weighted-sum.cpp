/*
ID: tiankonguse
TASK: D. Problem About Weighted Sum D. 关于加权和的问题
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/D
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "D-problem-about-weighted-sum"
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

int maxNM;

typedef long long ll;

struct SegTree {
  vector<ll> flag;    // 延迟标记
  vector<ll> sumVal;  // 内部 B 的个数
  vector<ll> mulVal;  // 内部 B 的个数
  vector<int> str;

  void Init(const vector<int>& nums) {
    int n = nums.size();
    maxNM = n + 1;
    flag.resize(maxNM << 2, 0);  // 全部打上延迟标记，都是 W 颜色
    mulVal.resize(maxNM << 2, 0);
    sumVal.resize(maxNM << 2, 0);

    str.resize(maxNM + 1, 0);
    for (int i = 1; i <= n; i++) {
      str[i] = nums[i - 1];
    }
  }

  void UpdateNode(int rt, int l, int r, ll v) {
    flag[rt] += v;
    sumVal[rt] += v * (r - l + 1);
    mulVal[rt] += v * (l + r) * (r - l + 1) / 2;
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    mulVal[rt] = mulVal[rt << 1] + mulVal[rt << 1 | 1];
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
      sumVal[rt] = str[l];
      mulVal[rt] = str[l] * l;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll v, int l = 1, int r = maxNM, int rt = 1) {
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
  pair<ll, ll> QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return {sumVal[rt], mulVal[rt]};
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (R <= m) {
      return QuerySum(L, R, lson);
    } else if (L > m) {
      return QuerySum(L, R, rson);
    } else {
      pair<ll, ll> leftRet = QuerySum(L, R, lson);
      pair<ll, ll> rightRet = QuerySum(L, R, rson);
      return {leftRet.first + rightRet.first, leftRet.second + rightRet.second};
    }
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
    int op;
    scanf("%d", &op);

    if (op == 1) {
      int l, r, d;
      scanf("%d%d%d", &l, &r, &d);
      segTree.Update(l, r, d);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      auto [sum, mul] = segTree.QuerySum(l, r);
      printf("%lld\n", mul - sum * (l - 1));
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