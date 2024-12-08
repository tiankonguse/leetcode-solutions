
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
/*
线段树：区间单点更新，修改查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Bulid();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 2e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
typedef pair<ll, ll> Point;
struct SegTree {
  vector<Point> minVal;  // 记录最值的位置  {x, y}

  void Init(int n) {
    maxNM = n + 1;
    minVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = {INT_MAX, INT_MAX};
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, Point add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      minVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, lson);
    if (L > m) Update(L, add, rson);
    PushUp(rt, l, r);
  }
  Point QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    Point ret = {INT_MAX, INT_MAX};  // 求最小值，初始值设置为最大值
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

class Solution {
 public:
  long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
    int n = xCoord.size();
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
      ll x = xCoord[i];
      ll y = yCoord[i];
      points[i] = {x, y};
    }
    sort(points.begin(), points.end());

    vector<ll> yh = {yCoord.begin(), yCoord.end()};
    sort(yh.begin(), yh.end());
    yh.erase(unique(yh.begin(), yh.end()), yh.end());
    const int yn = yh.size();
    unordered_map<ll, ll> YH;
    for (int i = 0; i < yn; i++) {
      YH[yh[i]] = i;
      // printf("Y: v=%lld -> %d\n", yh[i], i);
    }

    vector<ll> xh = {xCoord.begin(), xCoord.end()};
    sort(xh.begin(), xh.end());
    xh.erase(unique(xh.begin(), xh.end()), xh.end());
    const int xn = xh.size();
    unordered_map<ll, ll> XH;
    for (int i = 0; i < xn; i++) {
      XH[xh[i]] = i;
      // printf("X: v=%lld -> %d\n", xh[i], i);
    }

    vector<vector<ll>> Xarray(xn);
    for (int i = 0; i < n; i++) {
      auto [x, y] = points[i];
      Xarray[XH[x]].push_back(YH[y]);
    }
    for (int i = 0; i < xn; i++) {
      sort(Xarray[i].begin(), Xarray[i].end());
      // printf("X[%d]: ", i);
      // for(auto v: Xarray[i]){
      //   printf("->%lld", v);
      // }
      // printf("\n");
    }

    vector<vector<ll>> Yarray(yn);
    for (int i = 0; i < n; i++) {
      auto [x, y] = points[i];
      Yarray[YH[y]].push_back(XH[x]);
    }
    for (int i = 0; i < yn; i++) {
      sort(Yarray[i].begin(), Yarray[i].end());
      // printf("Y[%d]: ", i);
      // for(auto v: Yarray[i]){
      //   printf("->%lld", v);
      // }
      // printf("\n");
    }

    segTree.Init(yn);
    segTree.Bulid();
    for (int i = 0; i < yn; i++) {
      Point p = {Yarray[i].front(), i};
      segTree.Update(i + 1, p);
    }

    ll ans = -1;
    ll preX = -1;
    for (int i = 0; i < n; i++) {  // 枚举 points[i]
      auto [x, y] = points[i];
      ll X0 = XH[x];
      ll Y0 = YH[y];
      if (X0 != preX) {
        // 处理到新的第 X 列，X 列的所有 Y 肯定在线段树里， 更新线段树
        for (ll XY : Xarray[X0]) {
          auto it = upper_bound(Yarray[XY].begin(), Yarray[XY].end(), X0);
          Point p = {INT_MAX, INT_MAX};
          if (it != Yarray[XY].end()) {
            p = {*it, XY};
          }
          segTree.Update(XY + 1, p);
        }
        preX = X0;
      }

      // 查找 X1
      auto it1 = upper_bound(Xarray[X0].begin(), Xarray[X0].end(), Y0);
      if (it1 == Xarray[X0].end()) {
        continue;  // 同一列没有下一个
      }
      const auto [X1, Y1] = Point{X0, *it1};

      // 根据大小顺序关系，区间最小值肯定是右下角坐标
      auto [X2, Y2] = segTree.QueryMin(Y0 + 1, Y1 + 1);
      if (X2 == INT_MAX || Y2 != Y0) {
        continue;  // 右边没有点了
      }

      auto it3 = upper_bound(Xarray[X2].begin(), Xarray[X2].end(), Y2);
      if (it3 == Xarray[X2].end() || *it3 != Y1) {
        continue;  // 同一列没有下一个
      }
      const auto [X3, Y3] = Point{X2, *it3};

      ans = max(ans, (xh[X3] - xh[X1]) * (yh[Y1] - yh[Y0]));
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& xCoord, const vector<int>& yCoord, const ll ans) {
  TEST_SMP2(Solution, maxRectangleArea, ans, xCoord, yCoord);
}

int main() {
  Test({1, 1, 3, 3}, {1, 3, 1, 3}, 4);
  return 0;
}

#endif

/*
输入： xCoord = [1,1,3,3], yCoord = [1,3,1,3]
输出： 4


*/