// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

/*

v1,n1: (v1-q+1)*n1 = v1 * n1 - (q  - 1)* n1
...
vk,nk: vk * nk - (q - 1) * n2
sum(a,b) = sum(vi * ni) - (q-1) * sum(ni)

map<vi, ni> h;


p: 0 1 2 3 4 5 5 6 7
v: 0 1 0 1 0 1 0 1 1
   8 7 6 5 4 3 2 2 9
v: 0 1 0 1 1 1 0 1 1
   4 3 2 2 2 3 2 2 5




完美分裂或合并:
010 <=> 000
101 <=> 111

边缘分裂或合并:
001 <=> 011
*/

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)
typedef long long ll;

/*
线段树：区间单点更新，修改查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/
// 1.Build(); 2.query(a,b) 3.update(a,b)
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
    for (int i = 0; i < maxNM; i++) {
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
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    ranges[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = str[l];  // 如果 str 没有复制一份，则需要注意边界是否越界
      minVal[rt] = maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
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
  int n;
  map<int, int> h;
  vector<int> colors;

  int Len(int from, int to) {
    if (from > to) {
      return to + n - from + 1;
    } else {
      return to - from + 1;
    }
  }
  void Add(int from, int to) {
    if (from != to) {
      int v = Len(from, to);
      segTreeVN.Update(v, v);
      segTreeN.Update(v, 1);
      myprintf("add [%d, %d] v=%d\n", from, to, v);
      h[from] = to;
    }
  };
  void Remove(int from, int to) {
    if (from != to) {
      int v = Len(from, to);
      segTreeVN.Update(v, -v);
      segTreeN.Update(v, -1);
      myprintf("remove [%d, %d] v=%d\n", from, to, v);
      h.erase(from);
    }
  };

  int Pre(int i) {
    i = (i + n - 1) % n;
    return i;
  }

  int Next(int i) {
    i = (i + n + 1) % n;
    return i;
  }
  map<int, int>::iterator preIt(map<int, int>::iterator it) {
    if (it == h.begin()) {
      it = h.end();
    }
    it--;
    return it;
  }

 public:
  vector<int> numberOfAlternatingGroups(vector<int>& colors_,
                                        vector<vector<int>>& queries) {
    colors.swap(colors_);
    n = colors.size();
    segTreeVN.Init(n);
    segTreeVN.Build();
    segTreeN.Init(n);
    segTreeN.Build();

    // 计算中间的交替数组
    int from = 0;
    for (int i = 1; i < n; i++) {
      if (colors[i] == colors[i - 1]) {
        int to = i - 1;
        Add(from, to);
        Add(i - 1, i);
        from = i;
      }
    }

    Add(from, n - 1);
    if (h.size() == 1) {  // 如果未发现交替数组，说明从0到n-1是交替的
      if (colors.front() == colors.back()) {
        Add(n - 1, 0);
      }
    } else {
      if (colors.front() == colors.back()) {
        Add(n - 1, 0);
      } else {  // 前后可以连起来
        if (colors[0] == colors[1]) {
          Remove(from, n - 1);
          Add(from, 0);
        } else {
          int to = h[0];
          Remove(from, n - 1);
          Remove(0, to);
          Add(from, to);
        }
      }
    }
    myprintf("hash: \n");
    for (auto [from, to] : h) {
      myprintf("%d->%d\n", from, to);
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int op = q[0];
      if (op == 1) {
        int len = q[1];
        /*
        v1,n1: (v1-q+1)*n1 = v1 * n1 - (q  - 1)* n1
        ...
        vk,nk: vk * nk - (q - 1) * n2
        sum(a,b) = sum(vi * ni) - (q-1) * sum(ni)
        */
        if (h.size() == 1) {
          ans.push_back(n);
          continue;
        }
        int l = len;
        int r = n;
        int nv = segTreeVN.QuerySum(l, r);
        int ni = segTreeN.QuerySum(l, r);
        int v = nv - (l - 1) * ni;
        myprintf("[%d,%d] nv=%d ni=%d v=%d\n", l, r, nv, ni, v);
        ans.push_back(v);
      } else {
        const int index = q[1];
        const int value = q[2];
        myprintf("update: index=%d value=%d\n", index, value);
        if (colors[index] == value) {
          myprintf("no update\n");
          continue;  // 没有变更
        }

        /*
        完美分裂或合并:
        010 <=> 000
        101 <=> 111

        边缘分裂或合并:
        001 <=> 011
        */

        const int preIndex = Pre(index);
        const int nextIndex = Next(index);
        myprintf("preIndex=%d index=%d nextIndex=%d\n", preIndex, index,
                 nextIndex);

        if (colors[preIndex] != colors[index] &&
            colors[index] != colors[nextIndex]) {
          // 完美拆分 010 => 000 || 101 => 111
          if (h.size() == 1) {  // 整个环都满足
            int from = 0;
            int to = n - 1;
            Remove(from, to);
            Add(preIndex, index);
            Add(index, nextIndex);
            Add(nextIndex, preIndex);
          } else {
            auto it = h.upper_bound(index);
            it = preIt(it);

            int from = it->first;
            int to = it->second;
            Remove(from, to);
            Add(from, preIndex);
            Add(preIndex, index);
            Add(index, nextIndex);
            Add(nextIndex, to);
          }

        } else if (colors[preIndex] == colors[index] &&
                   colors[index] == colors[nextIndex]) {
          // 完美合并 000 => 010 || 111 => 101
          auto it = h.lower_bound(preIndex);
          it = preIt(it);

          int preFrom = it->first;
          int preTo = it->second;
          Remove(preFrom, preTo);
          Remove(preIndex, index);
          Remove(index, nextIndex);

          if (preFrom == nextIndex) {  // 整个环都满足
            int from = 0;
            int to = n - 1;
            Add(from, to);
          } else {
            it = h.lower_bound(nextIndex);
            int nextFrom = it->second;
            int nextTo = it->second;
            Remove(nextFrom, nextTo);
            Add(preFrom, nextTo);
          }
        } else if (colors[preIndex] == colors[index] &&
                   colors[index] != colors[nextIndex]) {
          // 左侧边缘翻转 001 => 011 || 110 => 100
          int prePreIndex = Pre(preIndex);

          if (colors[prePreIndex] == colors[preIndex]) {
            // 左侧边缘翻转  0001 => 0011 || 1110 => 1100
            myprintf("xxy: 0001 => 0011 || 1110 => 1100 \n");
            auto rightIt = h.lower_bound(index);
            int nextFrom = rightIt->first;
            int nextTo = rightIt->second;
            Remove(nextFrom, nextTo);
            Add(index, nextIndex);
            Add(nextIndex, nextTo);
          } else {
            // 1001 => 1011  || 0110 => 0100
            myprintf("xxy: 1001 => 1011  || 0110 => 0100 \n");
            auto leftIt = h.lower_bound(preIndex);
            leftIt = preIt(leftIt);

            int preFrom = leftIt->first;
            int preTo = leftIt->second;
            Remove(preFrom, preTo);
            Remove(preIndex, index);

            if (h.size() == 0) {  // 边界不同，其他都相同
              Add(index, nextIndex);
              Add(nextIndex, index);
            } else {
              auto rightIt = h.lower_bound(index);
              int nextFrom = rightIt->first;
              int nextTo = rightIt->second;
              Remove(nextFrom, nextTo);

              Add(preFrom, index);
              Add(index, nextIndex);
              Add(nextIndex, nextTo);
            }
          }

        } else if (colors[preIndex] != colors[index] &&
                   colors[index] == colors[nextIndex]) {
          // 右侧边缘翻转 011 => 001 || 100 => 110
          int nextNextIndex = Next(nextIndex);
          if (colors[nextIndex] == colors[nextNextIndex]) {
            // 0111 => 0011 || 1000 => 1100
            myprintf("xyy: 0111 => 0011 || 1000 => 1100");
            auto leftIt = h.lower_bound(index);
            leftIt = preIt(leftIt);
            int preFrom = leftIt->first;
            int preTo = leftIt->second;
            Remove(preFrom, preTo);
            Add(preFrom, preIndex);
            Add(preIndex, index);

          } else {
            // 0110 => 0010 || 1001 => 1101
            myprintf("xyy: 0110 => 0010 || 1001 => 110\n1");
            auto leftIt = h.lower_bound(index);
            leftIt = preIt(leftIt);
            int preFrom = leftIt->first;
            int preTo = leftIt->second;
            Remove(preFrom, preTo);
            Remove(index, nextIndex);

            if (h.size() == 0) {
              Add(index, preIndex);
              Add(preIndex, index);
            } else {
              auto rightIt = h.lower_bound(nextIndex);
              int nextFrom = rightIt->first;
              int nextTo = rightIt->second;
              Remove(nextFrom, nextTo);

              Add(preFrom, preIndex);
              Add(preIndex, index);
              Add(preIndex, nextTo);
            }
          }
        }
        colors[index] = value;

        myprintf("op hash: \n");
        for (auto [from, to] : h) {
          myprintf("%d->%d\n", from, to);
        }
      }
    }

    return ans;
  }
};
