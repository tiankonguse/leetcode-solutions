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
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

/*
基本功能：单点查询、单点更新
高级功能：区间查询、区间更新、

求面积:
1) 坐标离散化
2) 垂直边按x坐标排序
3) 从左往右用线段树处理垂直边
   累计每个离散x区间长度和线段树长度的乘积

求周长:
1) 坐标离散化
2) 垂直边按x坐标排序, 第二关键字为入边优于出边
3) 从左往右用线段树处理垂直边
   在每个离散点上先加入所有入边, 累计线段树长度变化值
   再删除所有出边, 累计线段树长度变化值
4) 水平边按y坐标排序, 第二关键字为入边优于出边
5) 从上往下用线段树处理水平边
   在每个离散点上先加入所有入边, 累计线段树长度变化值
   再删除所有出边, 累计线段树长度变化值


*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 111111;

int maxNM;

struct SegTree {
  LL minVal[maxn << 2];
  LL SumMal[maxn << 2];

  LL str[maxn];

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    SumMal[rt] = SumMal[rt << 1] + SumMal[rt << 1 | 1];
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = SumMal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  LL querySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return SumMal[rt];
    }

    int m = (l + r) >> 1;
    LL ret = 0;
    if (L <= m) {
      ret += querySum(L, R, lson);
    }
    if (m < R) {
      ret += querySum(L, R, rson);
    }
    return ret;
  }
  LL queryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    LL ret = inf;
    if (L <= m) {
      ret = min(ret, queryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, queryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree lineSegTree;
int leftPos[maxn];
int rightPos[maxn];

class Solution {
  int n;

  void initLeft(vector<int>& nums) {
    stack<int> sta;
    for (int i = 1; i <= n; i++) {
      while (!sta.empty() && nums[i - 1] <= nums[sta.top() - 1]) {
        sta.pop();
      }

      if (sta.empty()) {
        leftPos[i] = 1;
      } else {
        leftPos[i] = sta.top() + 1;
      }

      sta.push(i);
    }
  }
  void initRight(vector<int>& nums) {
    stack<int> sta;
    for (int i = n; i >= 1; i--) {
      while (!sta.empty() && nums[i - 1] <= nums[sta.top() - 1]) {
        sta.pop();
      }

      if (sta.empty()) {
        rightPos[i] = n;
      } else {
        rightPos[i] = sta.top() - 1;
      }
      sta.push(i);
    }
  }

 public:
  int maxSumMinProduct(vector<int>& nums) {
    n = nums.size();
    maxNM = n;

    initLeft(nums);
    initRight(nums);

    memset(lineSegTree.str, 0, sizeof(int) * (n * 2 + 1));
    for (int i = 1; i <= n; i++) {
      lineSegTree.str[i] = nums[i - 1];
    }

    lineSegTree.Build(1, n);

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      int l = leftPos[i];
      int r = rightPos[i];
      ll sum = lineSegTree.querySum(l, r, 1, n);
      ans = max(ans, sum * v);
    }

    return ans % mod;
  }
};

int main() {
  TEST_SMP1(Solution, maxSumMinProduct, 14, vector<int>({1, 2, 3, 2}));

  return 0;
}
