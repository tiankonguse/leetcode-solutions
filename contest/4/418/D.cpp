// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const int N = 1e5 + 100;
class Solution {
  vector<int> nums;
  int n;
  vector<ll> factors;
  void Init(vector<int>& nums_) {  //
    nums.swap(nums_);

    ll maxVal = 0;
    for (ll v : nums) {
      maxVal = max(maxVal, v);
    }

    n = nums.size();
    factors.resize(maxVal + 1);

    // n sqrt(n) 的复杂度计算出所有因子

    for (ll i = 0; i < n; i++) {
      const ll v = nums[i];
      maxVal = max(maxVal, v);
      const ll sq = sqrt(v);
      for (ll a = 1; a <= sq; a++) {
        if (v % a == 0) {
          factors[a]++;
          const ll b = v / a;
          if (a != b) {
            factors[b]++;
          }
        }
      }
    }
    vector<ll> gcdNums(maxVal + 1, 0);
    for (ll v = 1; v <= maxVal; v++) {
      if (factors[v] > 1) {
        gcdNums[v] = factors[v] * (factors[v] - 1) / 2;
      }
    }

    // 1 2 3 5 2*3 2*5 3*5 2*3*5
    for (ll v = maxVal; v > 1; v--) {
      if (gcdNums[v] == 0) continue;
      // 有若干个数字，gcd() = i
      const ll sq = sqrt(v);
      for (ll a = 1; a <= sq; a++) {
        if (v % a != 0) continue;
        gcdNums[a] -= gcdNums[v];

        const ll b = v / a;
        if (a != b && b != v) {
          gcdNums[b] -= gcdNums[v];
        }
      }
    }

    ll pre = 0;
    for (int v = 1; v <= maxVal; v++) {
      if (gcdNums[v] == 0) continue;
      pre += gcdNums[v];
      sums[pre] = v;
    }
  }
  map<ll, ll> sums;

 public:
  vector<int> gcdValues(vector<int>& nums_, vector<long long>& queries) {
    Init(nums_);
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto q : queries) {
      q++;
      ans.push_back(sums.lower_bound(q)->second);
    }
    return ans;
  }
};