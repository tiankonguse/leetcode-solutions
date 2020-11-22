#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
int maxSum = 0;

class SegTree {
  vector<vector<int>>* ptasks;
  pair<int, int> sum[max5 << 2];  //<val, pos>
  int n;

 public:
  void init(vector<vector<int>>& tasks) {
    ptasks = &tasks;
    n = ptasks->size();
  }

  pair<int, int> operate(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) {
      return a;
    } else if (a.first > b.first) {
      return b;
    } else {
      return a;
    }
  }
  void PushUp(int rt) { sum[rt] = operate(sum[rt << 1], sum[rt << 1 | 1]); }
  void bulid(int l = 1, int r = -1, int rt = 1) {
    if (r == -1) r = n;
    if (l == r) {
      sum[rt] = {(*ptasks)[l - 1][0], l};
      return;
    }
    int m = (l + r) >> 1;
    bulid(lson);
    bulid(rson);
    PushUp(rt);
  }
  pair<int, int> query(int L, int R, int l = 1, int r = -1, int rt = 1) {
    if (r == -1) r = n;
    if (L <= l && r <= R) {
      return sum[rt];
    }
    int m = (l + r) >> 1;
    pair<int, int> ret = {maxSum, -1};
    if (L <= m) ret = operate(ret, query(L, R, lson));
    if (R > m) ret = operate(ret, query(L, R, rson));
    return ret;
  }
  void update(int p, int add, int l = 1, int r = -1, int rt = 1) {
    if (r == -1) r = n;
    if (l == r) {
      sum[l] = {add, l};
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      update(p, add, lson);
    } else {
      update(p, add, rson);
    }
    PushUp(rt);
  }
};

SegTree segTree;
class Solution {
  bool check(int initVal, vector<vector<int>>& tasks) {
    segTree.init(tasks);
    segTree.bulid();

    int num = tasks.size();
    while (num--) {
      vector<int> v = {initVal, 0};
      auto it = upper_bound(tasks.begin(), tasks.end(), v);
      if (it == tasks.begin()) {
        return false;
      }
      int index = it - tasks.begin();
      index--;

      auto p = segTree.query(1, index);
      if (p.first == maxSum) {
        return false;
      }
      initVal -= p.first;
      segTree.update(p.second, maxSum);
    }

    return true;
  }

 public:
  int minimumEffort(vector<vector<int>>& tasks) {
    sort(tasks.begin(), tasks.end(),
         [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });

    ll left = 0, right = 0;
    for (auto& p : tasks) {
      if (p[0] > p[1]) {
        p[1] = p[0];
      }
      left += p[0];
      right += p[1];
    }
    // [left, right]
    maxSum = right + 1;

    while (left < right) {
      printf("left=%lld right=%lld\n", left, right);
      ll mid = (left + right) / 2;
      if (check(mid, tasks)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};

int main() {
  TEST_SMP1(Solution, minimumEffort, 8,
            vector<vector<int>>({{1, 2}, {2, 4}, {4, 8}}));

  return 0;
}
