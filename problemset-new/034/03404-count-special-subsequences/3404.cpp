
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; (t = x % y); x = y, y = t);
  return y;
}

class Solution {
  unordered_map<ll, ll> H;
  ll Hash(int a, int b) { return a * 10000 + b; }
  void Add(int a, int b) {
    const int c = Gcd(a, b);
    a /= c;
    b /= c;
    H[Hash(a, b)]++;
  }
  ll Search(int a, int b) {
    const int c = Gcd(a, b);
    a /= c;
    b /= c;
    ll h = Hash(a, b);
    if (H.count(h)) {
      return H[h];
    }
    return 0;
  }

 public:
  long long numberOfSubsequences(vector<int>& nums) {
    int n = nums.size();
    // p0 < p1 < p2 < p3
    // 0  1  2 3  4 5  6
    // p0 * p2 = p1 * p3
    // p0 / p1 = p3 / p2

    ll ans = 0;
    for (int p2 = 0; p2 < n; p2++) {
      // update p0 / p1
      int p1 = p2 - 2;
      for (int p0 = 0; p0 + 1 < p1; p0++) {
        Add(nums[p0], nums[p1]);
      }

      // search p3 / p2
      for (int p3 = p2 + 2; p3 < n; p3++) {
        ans += Search(nums[p3], nums[p2]);
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif