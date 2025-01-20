/*
ID: tiankonguse
TASK: G. Coprime Segment  G. Coprime 部分
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/G
PATH: ITMO Academy: pilot course » Two Pointers Method » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "G-coprime-segment"
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

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; (t = x % y); x = y, y = t);
  return y;
}

struct SegTree {
  vector<ll> gdbVal;
  vector<ll> str;

  void Init(vector<ll>& nums) {
    int n = nums.size();
    maxNM = n + 1;
    str.resize(maxNM+1, 1);
    gdbVal.resize(maxNM << 2, 0);
    for (int i = 1; i <= n; i++) {
      str[i] = nums[i - 1];
    }
  }

  ll Op(ll a, ll b) { return Gcd(a, b); }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    // int m = (l + r) >> 1;
    gdbVal[rt] = Op(gdbVal[rt << 1], gdbVal[rt << 1 | 1]);
  }

  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      gdbVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  ll QueryGcd(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return gdbVal[rt];
    }
    int m = (l + r) >> 1;
    if (L <= m && m < R) {
      return Op(QueryGcd(L, R, l, m, rt << 1), QueryGcd(L, R, m + 1, r, rt << 1 | 1));
    } else if (m < R) {
      return QueryGcd(L, R, m + 1, r, rt << 1 | 1);
    } else {
      return QueryGcd(L, R, l, m, rt << 1);
    }
  }
};

int n;
vector<ll> nums;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
}

SegTree segTree;

void Solver() {  //
  segTree.Init(nums);
  segTree.Build();
  int ans = n + 1;
  int r = 1;
  for (int l = 1; l <= n; l++) {  // [l, r]
    r = max(l, r);
    ll pre = segTree.QueryGcd(l, r);
    // printf("in: l=%d r=%d pre=%lld\n", l, r, pre);
    while (r < n && pre != 1) {
      r++;
      pre = Gcd(pre, nums[r - 1]);
    }
    // printf("out: l=%d r=%d pre=%lld\n", l, r, pre);
    if (pre == 1) {
      ans = min(ans, r - l + 1);
    } else {
      break;
    }
  }
  if (ans == n + 1) {
    ans = -1;
  }

  printf("%d\n", ans);
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