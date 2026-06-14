
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
  unordered_map<ll, ll> factorCount;
  void InitFactors(ll item) {
    for (ll i = 1; i * i <= item; i++) {
      if (item % i == 0) {
        ll j = item / i;
        factorCount[i]++;
        if (i != j) {
          factorCount[j]++;
        }
      }
    }
  }

 public:
  int maximumSaleItems(vector<vector<int>>& items, ll budget) {  //
    int n = items.size();
    for (auto& item : items) {
      int factor = item[0];
      InitFactors(factor);
    }
    vector<tuple<ll, ll, ll>> nums;
    nums.reserve(n + 1);
    ll minPrice = LLONG_MAX;
    for (int i = 0; i < n; i++) {
      ll factor = items[i][0];
      ll price = items[i][1];
      minPrice = min(minPrice, price);
      if (factorCount[factor] > 1) {
        nums.push_back({price, factorCount[factor] - 1, i});
      }
    }
    nums.push_back({minPrice * 2, 1, -1});
    sort(nums.begin(), nums.end());
    ll ans = 0;
    for (auto [price, count, index] : nums) {
      if (index >= 0) {
        if (price > budget) {
          continue;
        }
        ll cnt = min(count, budget / price);
        MyPrintf("budget=%lld price: %lld, index=%lld ans: +%lld\n", budget, price, index, cnt * 2);
        ans += cnt * 2;
        budget -= cnt * price;
      } else {
        price = price / 2;
        MyPrintf("budget=%lld price: %lld, index=%lld ans: +%lld\n", budget, price, index, budget / price);
        ans += budget / price;
        break;
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