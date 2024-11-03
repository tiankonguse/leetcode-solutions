
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

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
class Solution {
  vector<vector<vector<ll>>> dp;
  ll sum = 0;
  ll sum2 = 0;
  vector<ll> nums;

  ll Dfs(const ll n, const ll p0, const ll p1) {
    if (p0 < 0 || p1 < 0) return 0;
    if (n == -1) {
      if (p0 == 0 && p1 == 0) {
        return 1;
      }
      return 0;
    }

    ll& ret = dp[n][p0][p1];
    if (ret != -1) return ret;

    if (n == 1 && p0 == 4 && p1 == 0) {
      MyPrintf("n=%lld p0=%lld p1=%lld ------>\n", n, p0, p1);
      for (int i = 0; i < 10; i++) {
        if (nums[i] == 0) continue;
        MyPrintf("%d->[%lld] ", i, nums[i]);
      }
      MyPrintf("\n");
    }

    ret = 0;
    for (int i = 0; i < 10; i++) {
      if (nums[i] == 0) continue;
      nums[i]--;
      if (n % 2) {
        ret = (ret + Dfs(n - 1, p0, p1 - i)) % mod;
      } else {
        ret = (ret + Dfs(n - 1, p0 - i, p1)) % mod;
      }
      nums[i]++;
    }
    if (ret) {
      MyPrintf("n=%lld p0=%lld p1=%lld ret=%lld\n", n, p0, p1, ret);
      for (int i = 0; i < 10; i++) {
        if (nums[i] == 0) continue;
        MyPrintf("%d->[%lld] ", i, nums[i]);
      }
      MyPrintf("\n");
    }
    return ret;
  }

 public:
  int countBalancedPermutations(const string& num) {
    int n = num.size();
    nums.resize(10, 0);
    for (auto c : num) {
      nums[c - '0']++;
      sum += c - '0';
    }
    if (sum % 2 == 1) {
      return 0;
    }
    sum2 = sum / 2;
    // for (int i = 0; i < 10; i++) {
    //   MyPrintf("%d->[%lld] ", i, nums[i]);
    // }
    // MyPrintf("\n");
    MyPrintf("sum=%lld sum2=%lld n=%d\n", sum, sum2, n);
    dp.resize(n, vector<vector<ll>>(sum2 + 1, vector<ll>(sum2 + 1, -1)));
    return Dfs(n - 1, sum2, sum2);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& num, const int& ans) {
  TEST_SMP1(Solution, countBalancedPermutations, ans, num);
}

int main() {
  // Test("123", 2);
  // Test("112", 1);
  // Test("12345", 0);
  Test("08143", 12);
  // Test("1234", 8);
  // Test("0123", 8);
  // Test("01236", 12);
  return 0;
}

#endif