/*
ID: tiankonguse
TASK: A. Segment with the Maximum Sum A. 总和最大的段
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
PATH: ITMO 学院：试点课程 » 线段树，第 1 部分 » 步骤2 » 实践
submission: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/submission/298492829
*/
#define TASK "A-segment-maximum-sum"
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

typedef long long ll;
struct SegTree {
  vector<ll> maxVal;  // 子区间的最优值，至少1个
  vector<ll> preVal;  // 前缀最优值，至少1个
  vector<ll> sufVal;  // 后缀最优值，至少1个
  vector<ll> sumVal;
  vector<ll> str;

  void Init(vector<ll>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    maxVal.resize(maxNM << 2);
    preVal.resize(maxNM << 2);
    sufVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (size_t i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    preVal[rt] = max(preVal[rt << 1], sumVal[rt << 1] + preVal[rt << 1 | 1]);
    sufVal[rt] =
        max(sufVal[rt << 1] + sumVal[rt << 1 | 1], sufVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt], max(preVal[rt], sufVal[rt]));
    maxVal[rt] = max(maxVal[rt], sufVal[rt << 1] + preVal[rt << 1 | 1]);
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = preVal[rt] = sufVal[rt] = sumVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      maxVal[rt] += add;
      preVal[rt] += add;
      sufVal[rt] += add;
      sumVal[rt] += add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, lson);
    if (L > m) Update(L, add, rson);
    PushUp(rt, l, r);
  }
  ll QueryAllMax() { return max(maxVal[1], 0ll); }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QuerySum(L, R, lson);
    }
    if (m < R) {
      ret += QuerySum(L, R, rson);
    }
    return ret;
  }
};

int n, m;
vector<ll> nums;
void InitIO() {  //
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d", &n, &m);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
}

SegTree segTree;
void Solver() {  //
  segTree.Init(nums);
  segTree.Build();
  printf("%lld\n", segTree.QueryAllMax());
  while (m--) {
    int i;
    ll v;
    scanf("%d%lld", &i, &v);
    i++;
    const ll oldVal = segTree.QuerySum(i, i);
    segTree.Update(i, v - oldVal);
    printf("%lld\n", segTree.QueryAllMax());
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