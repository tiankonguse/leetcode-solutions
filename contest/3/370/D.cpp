// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class TreeArray {
 public:
  ll min_value;
  void Init(int n_) {
    n = n_;
    c.clear();
    min_value = ll(INT_MIN) * n;
    c.resize(n + 100, min_value);
  }

  ll Query(int x) {
    ll s = c[x];
    while (x > 0) {
      s = max(s, c[x]);
      x -= Lowbit(x);
    }
    return s;
  }

  void Update(int x, ll v) {
    while (x <= n) {
      c[x] = max(c[x], v);
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};

class Solution {
 public:
  long long maxBalancedSubsequenceSum(vector<int>& nums) {
    int n = nums.size();

    vector<pair<ll, int>> vals(n);
    for (int i = 0; i < n; i++) {
      vals[i] = {ll(nums[i]) - i, i};
    }
    sort(vals.begin(), vals.end());

    vector<int> index(n);
    for (int i = 0; i < n; i++) {
      index[vals[i].second] = i;
    }

    TreeArray treeArray;
    treeArray.Init(n);

    ll ans = nums.front();
    for (int i = 0; i < n; i++) {
      int pos = index[i] + 1;
      ll preSum = treeArray.Query(pos - 1);
      ll tmpAns = max(ll(nums[i]), nums[i] + preSum);
      treeArray.Update(pos, tmpAns);
      ans = max(ans, tmpAns);
      printf("i=%d ans=%lld\n", i, tmpAns);
    }

    return ans;
  }
};