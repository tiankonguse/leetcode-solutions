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

class DataOffline {
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

 private:
  int index;
  map<ll, int> m;
};

TreeArray treeArray;
DataOffline dataOffline;

class Solution {
 public:
  int countRangeSum(const vector<int>& nums, const int lower, const int upper) {
    ll sum = 0;
    dataOffline.Add(0);
    for (auto v : nums) {
      sum -= v;
      dataOffline.Add(v);
      dataOffline.Add(sum);
    }
    dataOffline.Build();

    int index = dataOffline.Size();

    treeArray.Init(index);

    int ans = 0;

    ll l = lower, r = upper;
    sum = 0;
    for (auto v : nums) {
      sum += v;
      l -= v, r -= v;
      ll val = v - sum;

      //   printf("v = %lld l = %lld, r = %lld m[v]=%d\n", v, l, r, m[val]);
      treeArray.Add(dataOffline.Get(val), 1);  //加入当前后缀

      // [left, right)
      int left = dataOffline.Lower(l);
      int right = dataOffline.Upper(r);

      if (left == right) {
        continue;
      }

      //   printf("left = %lld, right = %lld\n", left, right - 1);
      ans += treeArray.Query(left, right - 1);
    }

    return ans;
  }
};

int main() {
  TEST_SMP3(Solution, countRangeSum, 3, vector<int>({1, 3, 2, 3, 1}), -2, 2);
  TEST_SMP3(Solution, countRangeSum, 4,
            vector<int>({2147483647, -2147483648, -1, 0}), -1, 0);
  TEST_SMP3(Solution, countRangeSum, 3,
            vector<int>({-2147483647, 0, -2147483647, 2147483647}), -564, 3864);

  return 0;
}