
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

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

typedef long long ll;
class Solution {
 public:
  int sumOfGoodSubsequences(vector<int>& nums) {
    int n = nums.size();
    unordered_map<ll, ll> P;  // V->count 以V为结尾的好子序列个数
    unordered_map<ll, ll> S;  // V->sum 以V为结尾的好子序列的元素之和

    ll ans = 0;
    for (ll v : nums) {
      ll PV = (1 + P[v - 1] + P[v + 1]) % mod;
      ll SV = (v + S[v - 1] + P[v - 1] * v + S[v + 1] + P[v + 1] * v) % mod;
      ans = (ans + SV) % mod;
      P[v] = (P[v] + PV) % mod;
      S[v] = (S[v] + SV) % mod;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  TEST_SMP1(Solution, sumOfGoodSubsequences, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif