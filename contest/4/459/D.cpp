
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

typedef long long ll;
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}
class Solution {
 public:
  int countTrapezoids(const vector<vector<int>>& points) {
    int n = points.size();
    map<tuple<ll, ll, ll>, ll> lines;
    map<tuple<ll, ll>, ll> parallelLines;
    map<tuple<ll, ll, ll, ll>, ll> segments;
    map<tuple<ll, ll, ll>, ll> parallelSegments;

    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        ll x1 = points[i][0], y1 = points[i][1];
        ll x2 = points[j][0], y2 = points[j][1];
        // MyPrintf("i=%d (%lld, %lld)\n", i, x1, y1);
        // MyPrintf("j=%d (%lld, %lld)\n", j, x2, y2);
        // MyPrintf("----\n");

        // 第零步，标准化向量，方向朝右或者上
        if (x1 > x2 || (x1 == x2 && y1 > y2)) {
          swap(x1, x2);
          swap(y1, y2);
        }
        // 第一步，计算出向量
        const ll dx = x2 - x1, dy = y2 - y1;
        // 第二步：计算出向量的长度的平方
        const ll len2 = dx * dx + dy * dy;
        // 第三步：规范化向量，来代表斜率
        const ll g = Gcd(abs(dx), abs(dy));
        const ll nx = dx / g, ny = dy / g;
        // 第四步：直线使用 ax + by + c = 0 来表示，其中 a,b,c 为整数，且 a,b 互质
        const ll a = ny, b = -nx, c = nx * y1 - ny * x1;

        // 计算梯形的个数
        const tuple<ll, ll, ll> line = {a, b, c};
        const tuple<ll, ll> parallelLine = {a, b};
        if (parallelLines[parallelLine] - lines[line] > 0) {
          MyPrintf("i=%d (%lld, %lld)\n", i, x1, y1);
          MyPrintf("j=%d (%lld, %lld)\n", j, x2, y2);
          MyPrintf("a=%lld b=%lld c=%lld\n", i, j, a, b, c);
          printf("parallelLines=%lld, lines=%lld add=%lld\n", parallelLines[parallelLine], lines[line],
                 parallelLines[parallelLine] - lines[line]);
        }
        ans1 += parallelLines[parallelLine] - lines[line];
        parallelLines[parallelLine]++;
        lines[line]++;

        // 计算平行四边形的个数
        const tuple<ll, ll, ll, ll> segment = {a, b, c, len2};
        const tuple<ll, ll, ll> parallelSegment = {a, b, len2};
        ans2 += parallelSegments[parallelSegment] - segments[segment];
        parallelSegments[parallelSegment]++;
        segments[segment]++;
      }
    }
    MyPrintf("ans1=%lld, ans2=%lld\n", ans1, ans2);
    return ans1 - ans2 / 2;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif