// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

/*

v1,n1: (v1-q+1)*n1 = v1 * n1 - (q  - 1)* n1
vk,nk: vk * nk - (q - 1) * n2

sum(a,b) = sum(vi * ni) - (q-1) * sum(ni)

map<vi, ni> h;


0 1 0 1 0 1 0 1
0 1 0 1 1 1 0 1

完美分裂或合并:
010 <=> 000
101 <=> 111

边缘分裂或合并:
001 <=> 011
*/

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
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<pair<ll, int>> minVal;  // 记录最值的位置
  vector<pair<ll, int>> maxVal;  // 记录最值的位置
  vector<ll> sumVal;
  vector<pair<ll, ll>> ranges;
  vector<ll> str;

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i <= maxNM; i++) {
      str[i + 1] = default_val;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    ranges[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = str[l];  // 如果 str 没有复制一份，则需要注意边界是否越界
      minVal[rt] = maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      minVal[rt].first += add;
      maxVal[rt].first += add;
      sumVal[rt] += add * Num(ranges[rt]);
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, lson);
    if (L > m) Update(L, add, rson);
    PushUp(rt, l, r);
  }
  pair<ll, int> QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {-1, 0};
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
  pair<ll, int> QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {__LONG_LONG_MAX__, 0};  // 求最小值，初始值设置为最大值
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
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

SegTree segTreeVN;
SegTree segTreeN;
class Solution {
 public:
  vector<int> numberOfAlternatingGroups(vector<int>& colors,
                                        vector<vector<int>>& queries) {
    int n = colors.size();
    segTreeVN.Init(n);
    segTreeVN.Bulid();
    segTreeN.Init(n);
    segTreeN.Bulid();

    map<int, int> h;

    auto Add = [&n, &h](int from, int to) {
      if (from != to) {
        int v = to - from + 1;
        if (from > to) {
          v = to + n - from + 1;
        }
        segTreeVN.Update(v, v);
        segTreeN.Update(v, 1);
        h[from] = to;
      }
    };
    auto Remove = [&n, &h](int from, int to) {
      if (from != to) {
        int v = to - from + 1;
        if (from > to) {
          v = to + n - from + 1;
        }
        segTreeVN.Update(v, -v);
        segTreeN.Update(v, -1);
        h.erase(to);
      }
    };

    int from = 0;
    for (int i = 1; i < n; i++) {
      if (colors[i] == colors[i - 1]) {
        int to = i - 1;
        Add(from, to);
        Add(i - 1, i);
        from = i;
      }
    }

    if (h.size() == 0) {
      Add(0, n - 1);
      if (colors.front() == colors.back()) {  // 整个环都是交替的
        Add(n - 1, 0);
      }
    } else {
      if (colors.front() == colors.back()) {
        Add(from, n - 1);
        Add(n - 1, 0);
      } else {
        // 删除 0 开始的环
        int to = h[0];
        Remove(0, to);
        Add(from, to);
      }
    }
  }
};

// 0011