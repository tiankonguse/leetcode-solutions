// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

const int mod1e7 = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;
const ll BASE7 = 29;
const ll BASE9 = 29;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

ll hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}

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
};

SegTree segTree;
class Solution {
  vector<unordered_set<ll>> h;
  int n;
  int MAXANS;

 public:
  int minValidStrings(vector<string>& words, const string& target) {
    n = target.size();
    MAXANS = n + 1;
    h.resize(n + 1);

    for (auto& word : words) {
      ll pre7 = 0;
      for (int i = 0; i < word.size() && i < n; i++) {
        const char v = word[i];
        pre7 = (pre7 * BASE7 + (v - 'a' + 1)) % mod1e7;
        h[i + 1].insert(pre7);
      }
    }

    Init(target.data(), n);

    segTree.Init(n + 3, MAXANS);
    segTree.Bulid();
    segTree.Update(n + 1, -MAXANS);  // 整体右移一位

    for (int i = n; i >= 1; i--) {
      int l = i, r = n + 1;
      while (l < r) {
        int mid = (l + r) / 2;
        ll midHash = H(i - 1, mid - 1);
        int len = mid - i + 1;
        myprintf("i=%d l=%d r=%d mid=%d midHash=%lld len=%d\n", i, l, r, mid,
                 midHash, len);
        if (h[len].count(midHash)) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      if (r == i) {
        // 不存在
        myprintf("i=%d no exist\n", i);
        continue;
      }

      // [i, r] 都存在匹配,r 最大为 n
      // 需要查找 [i+1,n+1] 为结尾的答案
      ll val = 1 + segTree.QueryMin(i + 1, r).first;  // 线段树整体右移一位
      myprintf("i=%d val=%lld\n", i, val);
      if (val < MAXANS) {
        segTree.Update(i, val - MAXANS);
      }
    }
    int ans = segTree.QueryMin(1, 1).first;
    if (ans >= MAXANS) ans = -1;
    return ans;
  }
};