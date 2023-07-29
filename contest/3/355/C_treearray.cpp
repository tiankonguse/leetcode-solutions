// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_;
    t1.clear();
    t1.resize(n + 100, 0);
    t2.clear();
    t2.resize(n + 100, 0);
  }

  void AddEx(int l, int r, ll v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  void Add(int k, ll v) {
    ll v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  ll Query(int l, int r) {
    return (r + 1ll) * Query(t1, r) - 1ll * l * Query(t1, l - 1) -
           (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  ll Query(vector<ll>& t, int k) {
    ll ret = 0;
    while (k) {
      ret += t[k];
      k -= Lowbit(k);
    }
    return ret;
  }
  int Lowbit(int x) { return x & -x; }
  vector<ll> t1, t2;
  int n;
};
TreeArrayEx treeArray;
class Solution {
  int n;

  int Find(ll v) {  // 找到大于等于  v 的第一个位置
    int l = 1, r = n + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      ll V = treeArray.Query(mid, mid);
      if (V > v) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }

 public:
  int maxIncreasingGroups(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) { return a > b; });
    n = nums.size();
    treeArray.Init(n + 2);
    for (int i = 1; i <= n; i++) {
      treeArray.AddEx(i, i, nums[i - 1]);
    }
    // printf("n+1 = %d\n", treeArray.Query(n + 1, n + 1));

    int ans = 0;

    while (treeArray.Query(ans + 1, ans + 1) > 0) {
      ans++;

      ll v = treeArray.Query(ans, ans);
      printf("ans=%d v=%lld\n", ans, v);
      ll firstVal = treeArray.Query(1, 1);

      int R = 0;
      if (firstVal > v) {
        R = Find(v);
        printf("more L=%d R=%d\n", 1, R);
        treeArray.AddEx(1, R, -1);
      }

      int r = Find(v - 1);
      int left = ans - R;
      int l = r - left + 1;
      printf("less l=%d r=%d\n", l, r);
      treeArray.AddEx(l, r, -1);
    }
    printf("ans=%d\n", ans);

    return ans;
  }
};