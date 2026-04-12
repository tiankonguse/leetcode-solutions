
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
#include <bits/stdc++.h>
/*
线段树：单点更新，区间查询
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
  vector<ll> gcdVal;  // 记录最值的位置
  vector<ll> str;

  void Init(const vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    gcdVal.clear();
    gcdVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    ll leftVal = gcdVal[rt << 1];
    ll rightVal = gcdVal[rt << 1 | 1];
    if (leftVal == 0) {
      gcdVal[rt] = rightVal;
    } else if (rightVal == 0) {
      gcdVal[rt] = leftVal;
    } else {
      gcdVal[rt] = __gcd(leftVal, rightVal);
    }
    MyPrintf("PushUp: rt=%d, l=%d, r=%d, leftVal=%lld, rightVal=%lld, gcdVal=%lld\n", rt, l, r, leftVal, rightVal, gcdVal[rt]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      gcdVal[rt] = str[l];  // 如果 str 没有复制一份，则需要注意边界是否越界
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll val, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      gcdVal[rt] = val;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, val, lson);
    if (L > m) Update(L, val, rson);
    PushUp(rt, l, r);
  }
  ll QueryGcd(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (R < L) return 0;
    if (L <= l && r <= R) {
      return gcdVal[rt];
    }
    int m = (l + r) >> 1;
    ll leftVal = 0;
    ll rightVal = 0;
    if (L <= m) {
      leftVal = QueryGcd(L, R, lson);
    }
    if (m < R) {
      rightVal = QueryGcd(L, R, rson);
    }
    ll ret = 0;
    if (leftVal == 0) {
      ret = rightVal;
    } else if (rightVal == 0) {
      ret = leftVal;
    } else {
      ret = __gcd(leftVal, rightVal);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
    int n = nums.size();
    int ans = 0;
    unordered_set<int> HP;
    for (int i = 0; i < n; i++) {
      if (nums[i] % p == 0) {
        HP.insert(i);
      } else {
        nums[i] = 0;
      }
    }
    segTree.Init(nums);
    segTree.Build();
    for (int i = 0; i < n; i++) {
      MyPrintf("i=%d v=%d preGcd=%lld selfGcd=%d\n", i, nums[i], segTree.QueryGcd(1, i + 1),
               segTree.QueryGcd(i + 1, i + 1));
    }

    auto Check = [&]() -> bool {
      ll gcdVal = segTree.QueryGcd(1, n);
      MyPrintf("gcdVal=%lld\n", gcdVal);
      if (gcdVal != p) {
        MyPrintf("false: gcdVal[1,n]=%lld != p=%d\n", gcdVal, p);
        return false;
      }
      if (HP.size() < n) {
        MyPrintf("true: HP.size()=%d < n=%d\n", (int)HP.size(), n);
        return true;
      }
      if (HP.size() > 10) {
        MyPrintf("true: HP.size()=%d > 10\n", (int)HP.size());
        return true;
      }
      // 枚举删除一个，是否有答案
      for (auto idx : HP) {
        idx++;
        ll leftGcd = segTree.QueryGcd(1, idx - 1);
        ll rightGcd = segTree.QueryGcd(idx + 1, n);
        ll newGcd = 0;
        if (leftGcd == 0) {
          newGcd = rightGcd;
        } else if (rightGcd == 0) {
          newGcd = leftGcd;
        } else {
          newGcd = __gcd(leftGcd, rightGcd);
        }
        if (newGcd == p) {
          MyPrintf("true: delete idx=%d, leftGcd=%lld, rightGcd=%lld, newGcd=%lld\n", idx - 1, leftGcd, rightGcd,
                   newGcd);
          return true;
        }
      }
      MyPrintf("false: HP.size()=%d, but delete any one idx in HP, gcdVal[1,n] != p=%d\n", (int)HP.size(), p);
      return false;
    };

    for (auto& q : queries) {
      const int idx = q[0];
      const int val = q[1];
      if (HP.count(idx)) {
        HP.erase(idx);
        segTree.Update(idx + 1, 0);
        nums[idx] = 0;
      }
      if (val % p == 0) {
        HP.insert(idx);
        segTree.Update(idx + 1, val);
        nums[idx] = val;
      }
      MyPrintf("idx=%d, val=%d, HP.size()=%d\n", idx, val, (int)HP.size());
      if (Check()) {
        ans++;
      }
    }

    return ans;
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