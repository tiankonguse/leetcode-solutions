// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> sumVal;

  void Init(int n) {
    n++;
    maxNM = n;
    sumVal.clear();
    sumVal.resize(maxNM << 2, 0);
  }

  void PushUp(int rt) { sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1]; }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sumVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
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
SegTree segTree;
class Solution {
 public:
  int maxTotalReward(vector<int>& rewardValues) {
    sort(rewardValues.begin(), rewardValues.end());

    const int N = rewardValues.back() * 2 + 1;
    vector<int> flags(N, 0);
    set<int> finded, nofind;

    segTree.Init(N);
    segTree.Bulid();

    int ans = 0;

    flags[0] = 1;
    finded.insert(0);
    for (auto v : rewardValues) {
      finded.insert(v);
      flags[v] = 1;
      segTree.Update(v, v, 1);
      ans = max(ans, v);
    }

    nofind.insert(N);
    for (int i = 1; i < N; i++) {
      if (flags[i]) continue;
      nofind.insert(i);
    }

    vector<int> buf;
    buf.reserve(N);
    int pre = 0;
    for (const int v : rewardValues) {
      if (v == pre) continue;
      pre = v;  // 去重

      if (v == 1) continue;
      int leftNum = segTree.QuerySum(1, v - 1);  // 所有小于 v 的个数
      int rightNum = 0;

      auto calRight = [&N, &finded](int v) {
        if (v * 2 - 1 <= N - 1) {  // 没有越界
          //  实际的最大值是小于 v 的已经找到的最大值 + V
          auto itFinded = finded.lower_bound(v);
          itFinded--;  // 第一个小于
          return min(v + *itFinded, v * 2 - 1);
        } else {  // 越界
          int maxVal = N - 1 - v;
          auto itFinded = finded.upper_bound(maxVal);
          itFinded--;
          return min(v + *itFinded, N - 1);
        }
      };

      int l = v + 1;
      int r = min(v * 2 - 1, N - 1);
      if (l <= r) {  // [l,r]
        rightNum = (r - l + 1) - segTree.QuerySum(l, r);
      }
      printf("v=%d left=%d r=%d\n", v, leftNum, rightNum);

      if (true || leftNum <= rightNum) {  // 优先枚举左半部
        for (auto V : finded) {
          if (V >= v) break;
          int sum = V + v;
          ans = max(ans, sum);
          if (sum < N && flags[sum] == 0) {
            segTree.Update(sum, sum, 1);
            nofind.erase(sum);
            flags[sum] = 1;
            buf.push_back(sum);
          }
        }
        while (!buf.empty()) {
          finded.insert(buf.back());
          buf.pop_back();
        }
      } else {
        for (auto sum : nofind) {
          if (sum <= v) {
            buf.push_back(sum);
            continue;
            ;
          }
          if (sum > r) break;
          int V = sum - v;
          if (flags[V] == 1) continue;
          ans = max(ans, sum);

          segTree.Update(sum, sum, 1);
          finded.insert(sum);
          flags[sum] = 1;
          buf.push_back(sum);
        }
        while (!buf.empty()) {
          nofind.erase(buf.back());
          buf.pop_back();
        }
      }
    }

    return ans;
  }
};