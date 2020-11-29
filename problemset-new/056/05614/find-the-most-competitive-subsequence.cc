#include "base.h"



// lower_bound 大于等于
// upper_bound 大于

const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = max5;

const int kMaxVal = inf;
int maxNM;

struct SegTree {
  int sign[maxn << 2];                //
  pair<int, int> minVal[maxn << 2];  // val, pos
  int str[maxn];

  pair<int, int> mymin(pair<int, int> a, pair<int, int> b) {
    if (a.first <= b.first) {
      return a;
    } else {
      return b;
    }
  }

  void PushUp(int rt) {
    minVal[rt] = mymin(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      minVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    bulid(lson);
    bulid(rson);
    PushUp(rt);
  }

  pair<int, int> queryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    pair<int, int> ret = {kMaxVal, -1};
    if (L <= m) {
      ret = mymin(ret, queryMin(L, R, lson));
    }
    if (m < R) {
      ret = mymin(ret, queryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;

class Solution {
 public:
  vector<int> mostCompetitive(vector<int>& nums, int k) {
    int n = nums.size();
    if (k == n) {
      return nums;
    }
    maxNM = n;
    for (int i = 1; i <= n; i++) {
      segTree.str[i] = nums[i - 1];
    }
    segTree.bulid();

    vector<int> ans(k);
    int l = 1, r = n - k + 1;
    for (int i = 0; i < k; i++) {
      auto p = segTree.queryMin(l, r);
      ans[i] = p.first;
      l = p.second + 1, r++;
    }
    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, mostCompetitive, vector<int>({2,6}), vector<int>({3,5,2,6}), 2);
  TEST_SMP2(Solution, mostCompetitive, vector<int>({2,3,3,4}), vector<int>({2,4,3,3,5,4,9,6}), 4);
  return 0;
}
