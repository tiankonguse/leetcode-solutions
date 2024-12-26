#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;
// lower_bound 大于等于
// upper_bound 大于

const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = max5;
const int kMaxVal = inf;

int maxNM;

struct SegTree {
  LL sign[maxn << 2];  //
  LL minVal[maxn << 2];
  LL maxMal[maxn << 2];

  LL str[maxn];

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxMal[rt] = max(maxMal[rt << 1], maxMal[rt << 1 | 1]);
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      minVal[rt << 1] += sign[rt];
      minVal[rt << 1 | 1] += sign[rt];

      maxMal[rt << 1] += sign[rt];
      maxMal[rt << 1 | 1] += sign[rt];
      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      minVal[rt] = maxMal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      minVal[rt] += add;
      maxMal[rt] += add;
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, add, lson);
    if (R > m) update(L, R, add, rson);
    PushUp(rt);
  }
  LL queryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    LL ret = kMaxVal;
    if (L <= m) {
      ret = min(ret, queryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, queryMin(L, R, rson));
    }
    return ret;
  }
  LL queryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxMal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    LL ret = -1;
    if (L <= m) {
      ret = max(ret, queryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, queryMax(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;

class Solution {
 public:
  int minMoves(vector<int>& nums, int limit) {
    int n2 = nums.size();
    int n = n2 / 2;
    maxNM = 2 * limit;

    for (int i = 0; i <= maxNM; i++) {
      segTree.str[i] = 0;
    }
    segTree.Build();

    for (int i = 0; i < n; i++) {
      int x = nums[i], y = nums[n2 - i - 1];
      if (x > y) {
        swap(x, y);
      }

      if (2 <= x) {  //[2, x] => 2
        segTree.update(2, x, 2);
      }
      segTree.update(x + 1, y + limit, 1);
      segTree.update(x + y, x + y, -1);
      if (y + limit + 1 <= maxNM) {  // [y+limit+1, 2*limit] => 2
        segTree.update(y + limit + 1, maxNM, 2);
      }
    }
    return segTree.queryMin(2, maxNM);
  }
};

int main() {
  TEST_SMP2(Solution, minMoves, 1, vector<int>({3, 5, 2, 6}), 4);
  TEST_SMP2(Solution, minMoves, 2, vector<int>({1, 2, 2, 1}), 2);
  TEST_SMP2(Solution, minMoves, 0, vector<int>({1, 2, 1, 2}), 2);
  return 0;
}
