#include <bits/stdc++.h>
using namespace std;
#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;
template <class T>
using max_queue = priority_queue<T>;

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 55000, max6 = 2000100;

class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    memset(c, 0, sizeof(ll) * (n + 2));
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
  ll c[max5];
  int n;
};

class DiscreteArray {
 public:
  void Add(ll v) { m[v] = 0; }
  void Build() {
    index = 0;
    for (auto& p : m) {
      p.second = ++index;
    }
  }
  int Get(ll v) { return m[v]; }
  int Size() { return index; }
  int Lower(ll v) {
    auto it = m.lower_bound(v);
    if (it == m.end()) {
      return index + 1;
    }
    return it->second;
  }
  int Upper(ll v) {
    auto it = m.upper_bound(v);
    if (it == m.end()) {
      return index + 1;
    }
    return it->second;
  }
  void Reset(){
    m.clear();
  }

 private:
  int index;
  map<ll, int> m;
};

TreeArray treeArray;
DiscreteArray discreteArray;

class Solution {
 public:
  int reversePairs(const vector<int>& nums) {
    discreteArray.Reset();
    for (auto v : nums) {
      discreteArray.Add(v);
    }
    discreteArray.Build();

    int index = discreteArray.Size();
    treeArray.Init(index);

    int ans = 0;
    for (auto v : nums) {
      ll val = v;

      int it = discreteArray.Upper(val * 2);
      if (it <= index) {
        ans += treeArray.Query(it, index);
      }
      treeArray.Add(discreteArray.Get(val), 1);
    }

    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, reversePairs, 2, vector<int>({1, 3, 2, 3, 1}));
  TEST_SMP1(Solution, reversePairs, 3, vector<int>({2, 4, 3, 5, 1}));
  TEST_SMP1(Solution, reversePairs, 1, vector<int>({-5, -5}));

  return 0;
}