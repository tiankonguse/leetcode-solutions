// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
constexpr int inf = 1 << 30;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int kMaxVal = 10e8;

int maxNM;
const int BIT = 32;
int preBits[BIT][10001];
typedef long long ll;
struct SegTree {
  vector<int> minVal;

  void Init(int n) {
    n++;
    maxNM = n;
    minVal.resize(maxNM << 2);
  }

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void PushDown(int rt) {}
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      minVal[rt] = add;
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
  }
  int QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    int ret = INT_MAX;
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree seg[2];
int seg_now = 1;
int seg_pre = 0;
class Solution {
  int n;
  int m;
  vector<int> nums;
  vector<int> andValues;

  int maxBit;

  void Init() {
    n = nums.size();
    m = andValues.size();

    maxBit = 1;
    for (auto v : andValues) {
      int bit = 0;
      while (v) {
        bit++;
        v = v / 2;
      }
      maxBit = max(bit, maxBit);
    }
    for (auto v : nums) {
      int bit = 0;
      while (v) {
        bit++;
        v = v / 2;
      }
      maxBit = max(bit, maxBit);
    }
    printf("n=%d m=%d maxBit=%d\n", n, m, maxBit);
    for (int b = 0; b < maxBit; b++) {
      preBits[b][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      for (int b = 0; b < maxBit; b++) {
        // printf("i=%d b=%d preBits.size()=%d preBits[b].size()=%d\n", i, b,
        // preBits.size(), preBits[b].size());
        if ((v >> b) & 1) {
          preBits[b][i] = preBits[b][i - 1];
        } else {
          preBits[b][i] = preBits[b][i - 1] + 1;
        }
        // printf("i=%d b=%d\n", i, b);
      }
    }
    // printf("next 2 %d\n", __LINE__);
    for (int j = 0; j <= 1; j++) {
      seg[j].Init(n);
      seg[j].Build();
    }
  }

  // 找到最短的满足要求的子数组
  // 可能有答案的情况下，前缀分为三种情况： [0,a,b,n]
  // 1) [b+1,n] 是 val 的子集
  // 2) [a,b] == val
  // 3) val 是 [0, a-1] 的子集
  // 分四种情况
  // 1) now=0, val=0 任何是否都满足
  // 2) now=0, val=1 没有答案, 特殊处理
  // 3) now=1, val=0 左边必须有 0，一旦找到，答案都在左边, [1, val_exp_zero]
  // 4) now=1, val=1 左边不能有 0，一旦找到，答案都在右边, [val_exp_one, n]
  pair<int, int> FindRange(int n, int m) {
    // printf("next %s %d : \n", __FUNCTION__, __LINE__ - 9);
    // printf("n=%d m=%d\n", n, m);
    const int val = andValues[m - 1];  //
    // printf("next %s %d : \n", __FUNCTION__, __LINE__ - 9);
    const int now = nums[n - 1];
    int val_exp_zero = n;  // 取 min, [1, val_exp_zero]
    int val_exp_one = 1;   // 取 max, [val_exp_one, n]

    // printf("next %s %d : \n", __FUNCTION__, __LINE__ - 9);
    for (int b = 0; b < maxBit; b++) {
      const int now_bit = (now >> b) & 1;
      const int val_bit = (val >> b) & 1;
      const int bitNum = preBits[b][n];
      const auto bits = preBits[b];
      const int offset = std::lower_bound(bits, bits + n + 1, bitNum) - bits;
      if (now_bit == 0 && val_bit == 1) {
        return {-1, -1};
      } else if (now_bit == 1 && val_bit == 0) {
        if (bitNum == 0) {
          return {-1, -1};
        }
        // 第一个相等的，就是第一个 0， 需要找最后一个0
        val_exp_zero = min(val_exp_zero, offset);
      } else if (now_bit == 1 && val_bit == 1) {
        // 第一个相等，说明第一个是 0， 不能有0，所以是下一个
        val_exp_one = max(val_exp_one, offset + 1);
      } else {
        // do nothing
      }
    }
    // printf("next %s %d : \n", __FUNCTION__, __LINE__ - 9);

    if (val_exp_one > val_exp_zero) {
      return {-1, -1};  // 没有答案
    }

    // 答案是 [val_exp_one, val_exp_zero]
    return {val_exp_one, val_exp_zero};
  }

  // 对所有的 1 <= i <= m，nums[li] & nums[li + 1] & ... & nums[ri] ==
  // andValues[i] ，其中 & 表示按位AND运算符。
  ll Solver(int n, int m) {  // 前 n 个数字，拆分为 m 个的最优答案
    ll ret = inf;            // 代表没有答案

    const int expVal = andValues[m - 1];
    const int nowVal = nums[n - 1];
    if ((nowVal & expVal) != expVal) {  // 最后一个位置不满足，没有答案
      return ret;
    }

    // printf("next %s %d : \n", __FUNCTION__, __LINE__);
    auto [l, r] = FindRange(n, m);
    // printf("n=%d m=%d l=%d r=%d\n", n, m, l, r);
    if (r == -1) {
      return ret;
    }

    // printf("next %s %d : \n", __FUNCTION__, __LINE__);
    ll tmp = FindMin(l - 1, r - 1, m - 1);  // 前面不可划分
    if (tmp == inf) {
      return ret;
    }
    // printf("next %s %d : \n", __FUNCTION__, __LINE__);
    return ret = tmp + nowVal;
  }

  ll FindMin(int l, int r, int m) {
    if (m == 0) {
      if (0 >= l && 0 <= r) {
        return 0;
      } else {
        return inf;
      }
    } else {
      if (r == 0) {
        return inf;
      }
    }
    if (l < 1) {
      l = 1;
    }
    return seg[seg_pre].QueryMin(l, r);
  }

 public:
  int minimumValueSum(vector<int>& nums_, vector<int>& andValues_) {
    nums.swap(nums_);
    andValues.swap(andValues_);
    Init();
    // printf("next %d\n", __LINE__);
    for (int j = 1; j <= m; j++) {
      swap(seg_now, seg_pre);
      // seg[seg_now].Build();
      for (int i = 1; i <= n; i++) {
        // printf("next 0 %d\n", __LINE__);
        ll tmp = Solver(i, j);
        // printf("m=%d n=%d ans=%lld\n", j, i, tmp);
        // printf("next 1 %d\n", __LINE__);
        seg[seg_now].Update(i, i, tmp);

        // printf("next 2 %d\n", __LINE__);
      }
    }

    ll ans = Solver(n, m);
    if (ans == inf) {
      ans = -1;
    }
    return ans;
  }
};