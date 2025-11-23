
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  vector<int> sumAndMultiply(const string& s, vector<vector<int>>& queries) {
    int n = s.size();
    vector<ll> preSum(n + 1, 0);
    vector<pair<ll, ll>> preNum(n + 1, {0, 0});  // <val, count>
    vector<ll> base(n + 1, 1);
    for (int i = 1; i <= n; i++) {
      ll v = s[i - 1] - '0';
      preSum[i] = (preSum[i - 1] + v) % mod;
      preNum[i] = preNum[i - 1];
      base[i] = (base[i - 1] * 10) % mod;
      if (v == 0) continue;
      preNum[i].first = (preNum[i].first * 10 + v) % mod;
      preNum[i].second++;
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int l = q[0] + 1, r = q[1] + 1;
      ll sum = (preSum[r] - preSum[l - 1] + mod) % mod;
      auto [leftVal, leftCount] = preNum[l - 1];
      auto [rightVal, rightCount] = preNum[r];
      ll leftBaseVal = (leftVal * base[rightCount - leftCount]) % mod;
      ll val = (rightVal - leftBaseVal + mod) % mod;
      ans.push_back((sum * val) % mod);
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