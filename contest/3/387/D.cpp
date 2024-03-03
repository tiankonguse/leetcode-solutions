// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};
TreeArray tree1, tree2;
class Solution {
 public:
  vector<int> resultArray(vector<int>& nums) {
    int n = nums.size();
    map<int, int> H;
    for (auto v : nums) {
      H[v] = 0;
    }
    int base = 1;
    for (auto& [k, v] : H) {
      v = base++;
    }

    tree1.Init(n + 1);
    tree2.Init(n + 1);

    vector<int> ans(n);
    int l = 0, r = n - 1;

    int sum1 = 0;
    int sum2 = 0;
    auto Add1 = [&](int v) {
      ans[l++] = v;
      tree1.Add(H[v], 1);
      sum1++;
    };
    auto add2 = [&](int v) {
      ans[r--] = v;
      tree2.Add(H[v], 1);
      sum2++;
    };

    for (const auto v : nums) {
      const int V = H[v];
      if (l == 0) {
        Add1(v);
      } else if (r == n - 1) {
        add2(v);
      } else {
        const int g1 = tree1.Query(V + 1, n + 1);
        const int g2 = tree2.Query(V + 1, n + 1);
        if (g1 > g2) {
          Add1(v);
        } else if (g1 < g2) {
          add2(v);
        } else {
          if (sum1 <= sum2) {
            Add1(v);
          } else {
            add2(v);
          }
        }
      }
    }
    std::reverse(ans.begin() + l, ans.end());
    return ans;
  }
};