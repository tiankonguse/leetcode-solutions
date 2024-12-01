/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "demo"
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
struct SegTree {
  vector<ll> sign;
  vector<ll> sumVal;
  vector<ll> countVal;
  vector<pair<ll, ll>> ranges;

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sign.clear();
    sumVal.clear();
    countVal.clear();
    ranges.clear();
    sign.resize(maxNM << 2, 0);
    sumVal.resize(maxNM << 2);
    countVal.resize(maxNM << 2);
    ranges.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    countVal[rt] = countVal[rt << 1] + countVal[rt << 1 | 1];
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      sumVal[rt << 1] += sign[rt] * Num(ranges[rt << 1]);
      sumVal[rt << 1 | 1] += sign[rt] * Num(ranges[rt << 1 | 1]);

      sign[rt] = 0;
    }
  }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    ranges[rt] = {l, r};
    if (l == r) {
      countVal[rt] = sumVal[rt] = 0;
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
      sumVal[rt] += add * Num(ranges[rt]);
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    PushDown(rt);
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
map<ll, int> H;
vector<ll> V;
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
    i = vi++;
    V[i] = v;
  }

  vector<tuple<ll, ll, ll, ll>> lines;
  lines.reserve(n * 2);
  for (int i = 0; i < n; i++) {
    lines.push_back({recs[i].a.x, 0, recs[i].a.y, recs[i].b.y});
    lines.push_back({recs[i].b.x, 1, recs[i].a.y, recs[i].b.y});
  }
  sort(lines.begin(), lines.end());

  ll ans = 0;
  // 初始化线段树
  segTree.Init(vi);
  segTree.Bulid();
  // 只求竖线，不求横线
  for (auto [x, op, y0, y1] : lines) {
    int l = H[y0], r = H[y1];
    if (op == 0) {  // 矩阵进入，左边界
      ll oldLine = segTree.QuerySum(1, vi);
      segTree.Update(l, r, 1);
      ll newLine = segTree.QuerySum(1, vi);
      ans += newLine - oldLine;

    } else {  // 矩阵退出，右边界
    }
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/