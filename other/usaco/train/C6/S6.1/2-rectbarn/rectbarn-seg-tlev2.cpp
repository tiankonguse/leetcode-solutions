/*
ID: tiankonguse
TASK: rectbarn
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "rectbarn"
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
  vector<ll> minVal;  // 记录最值的位置
  const vector<int>* str;

  void Init(int n, const vector<int>& rows) {
    maxNM = n + 1;
    minVal.resize(maxNM << 2);
    str = &rows;
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = (*str)[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = __LONG_LONG_MAX__;  // 求最小值，初始值设置为最大值
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;

int n, m, P;
vector<pair<int, int>> ps;
vector<int> rows;
void Solver() {  //
  scanf("%d%d%d", &n, &m, &P);
  ps.resize(P);
  for (int i = 0; i < P; i++) {
    scanf("%d%d", &ps[i].first, &ps[i].second);
  }
  sort(ps.begin(), ps.end());

  ll ans = 0;
  rows.resize(m + 10, 0);

  auto FindLeft = [](const int x, const ll h) {
    int l = 1, r = x;  // (1,x]
    while (l < r) {
      int mid = (l + r) / 2;
      const ll v = segTree.QueryMin(mid, x);
      if (v >= h) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  };
  auto FindRight = [](const int x, const ll h) {
    int l = x, r = m + 1;  // [x, n)
    while (l < r) {
      int mid = (l + r) / 2;
      const ll v = segTree.QueryMin(x, mid);
      if (v >= h) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  };

  int p = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      rows[j]++;
    }
    while (p < P && ps[p].first == i) {  // 障碍物，高度至 0
      const int y = ps[p].second;
      rows[y] = 0;
      p++;
    }
    segTree.Init(m + 1, rows);
    segTree.Build();

    for (int j = 1; j <= m; j++) {  // 枚举 r 为最低点，二分左右最远距离
      const ll h = rows[j];
      if(h == 0)continue;
      const int L = FindLeft(j, h);
      const int R = FindRight(j, h);
      //   printf("i=%d j=%d h=%lld L=%d R=%d tmp=%lld\n", i, j, h, L, R,
      //          (R - L + 1) * h);
      ans = max(ans, (R - L + 1) * h);
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