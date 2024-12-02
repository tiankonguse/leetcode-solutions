/*
ID: tiankonguse
TASK: picture
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "picture"
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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Bulid();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;

map<ll, int> H;
vector<ll> V;
struct SegTree {
  vector<ll> sign;
  vector<ll> countVal;

  void Init(int n) {
    maxNM = n + 1;
    sign.clear();
    countVal.clear();
    sign.resize(maxNM << 2, 0);
    countVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    if (sign[rt]) {
      countVal[rt] = V[r] - V[l-1];
    } else if (l == r) {
      countVal[rt] = 0;
    } else {
      countVal[rt] = countVal[rt << 1] + countVal[rt << 1 | 1];
    }
    // if(countVal[rt])printf("rt=%d l=%d r=%d sum=%lld\n", rt, l, r, countVal[rt]);
  }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      countVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      PushUp(rt, l, r);
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  ll QueryAll() { return countVal[1]; }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return countVal[rt];
    }
    if (sign[rt]) {
      int ll = max(l, L);
      int rr = min(r, R);
      return V[rr] - V[ll-1];
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
SegTree segTree;

struct Point {
  ll x, y;
  void Read() { scanf("%lld%lld", &x, &y); }
};
struct Rec {
  Point a, b;
  void Read() { a.Read(), b.Read(); }
};

int n;
vector<Rec> recs;
ll ans = 0;

void Solver() {  //
  scanf("%d", &n);
  recs.resize(n);
  H[INT_MIN] = 0;
  H[INT_MAX] = 0;
  for (int i = 0; i < n; i++) {
    recs[i].Read();
    H[recs[i].a.x] = 0;
    H[recs[i].b.x] = 0;
    H[recs[i].a.y] = 0;
    H[recs[i].b.y] = 0;
  }

  // 离散化
  int vi = 1;
  V.resize(H.size() + 1);
  for (auto& [v, i] : H) {
    i = vi;
    V[i] = v;
    vi++;
  }
  // for (int i = 1; i < vi; i++) {
  //   printf("0: i=%d v=%lld\n", i, V[i]);
  // }
  // for (auto& [v, i] : H) {
  //   printf("1: i=%d v=%lld\n", i, v);
  // }

  vector<tuple<ll, ll, ll, ll>> lines;
  lines.reserve(n * 2);

  for (int i = 0; i < n; i++) {
    lines.push_back({recs[i].a.x, 0, recs[i].a.y, recs[i].b.y});
    lines.push_back({recs[i].b.x, 1, recs[i].a.y, recs[i].b.y});
  }
  sort(lines.begin(), lines.end());

  // 初始化线段树
  segTree.Init(vi);
  segTree.Bulid();
  // 只求竖线
  for (auto [x, op, LV, RV] : lines) {
    int l = H[LV], r = H[RV];
    // printf("x=%lld op=%lld LV=%lld[%d] RV=%lld[%d] ans=%lld\n", x, op, LV, l,
    //        RV, r, ans);
    if (op == 0) {  // 矩阵进入，左边界
      ll oldLine = segTree.QueryAll();
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      segTree.Update(l+1, r, 1);
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      ll newLine = segTree.QueryAll();
      ans += newLine - oldLine;
    } else {  // 矩阵退出，右边界
      ll oldLine = segTree.QueryAll();
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      segTree.Update(l+1, r, -1);
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      ll newLine = segTree.QueryAll();
      ans += oldLine - newLine;
    }
    // printf("x=%lld op=%lld LV=%lld[%d] RV=%lld[%d] ans=%lld\n", x, op, LV, l,
    //        RV, r, ans);
  }

  lines.clear();
  for (int i = 0; i < n; i++) {
    lines.push_back({recs[i].a.y, 0, recs[i].a.x, recs[i].b.x});
    lines.push_back({recs[i].b.y, 1, recs[i].a.x, recs[i].b.x});
  }
  sort(lines.begin(), lines.end());

  // 初始化线段树
  segTree.Init(vi);
  segTree.Bulid();
  // 只求竖线
  for (auto [x, op, LV, RV] : lines) {
    int l = H[LV], r = H[RV];
    if (op == 0) {  // 矩阵进入，左边界
      ll oldLine = segTree.QueryAll();
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      segTree.Update(l+1, r, 1);
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      ll newLine = segTree.QueryAll();
      ans += newLine - oldLine;
    } else {  // 矩阵退出，右边界
      ll oldLine = segTree.QueryAll();
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      segTree.Update(l+1, r, -1);
      // assert(segTree.QueryAll() == segTree.QuerySum(1, vi));
      ll newLine = segTree.QueryAll();
      ans += oldLine - newLine;
    }
  }

  printf("%lld\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/