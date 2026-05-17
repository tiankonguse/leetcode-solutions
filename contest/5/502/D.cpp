
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
const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 100010, max6 = 2000010;

const ll BASE1 = 100003, BASE2 = 100019;

class StringHash {
  ll h[max5];
  ll qpowCache[max5];
  const ll BASE;
  const ll MOD;

 public:
  StringHash(ll base, ll mod) : BASE(base), MOD(mod) {}
  ll H(int l, int r) {
    if (l == 0) return h[r];
    ll pre = h[l - 1] * qpowCache[r - l + 1] % MOD;
    return (h[r] - pre + MOD) % MOD;
  }

  void Init(vector<int>& str, int n) {
    qpowCache[0] = 1;
    for (int i = 1; i <= n; i++) {
      qpowCache[i] = (qpowCache[i - 1] * BASE) % MOD;
    }

    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre = (pre * BASE + str[i]) % MOD;
      h[i] = pre;
    }
  }
};

StringHash H1(BASE1, mod1e7);
StringHash H2(BASE2, mod1e9);

class Solution {
 public:
  int smallestUniqueSubarray(vector<int>& nums) {  //
    int n = nums.size();
    H1.Init(nums, n);
    H2.Init(nums, n);
    auto Check = [&](int len) -> bool {
      unordered_map<ll, int> seen;
      for (int i = 0; i + len <= n; i++) {
        ll hash1 = H1.H(i, i + len - 1);
        ll hash2 = H2.H(i, i + len - 1);
        ll combinedHash = (hash1 << 32) | hash2;
        seen[combinedHash]++;
      }
      for (const auto& [hash, count] : seen) {
        if (count == 1) {
          return true;
        }
      }
      return false;
    };
    int l = 1, r = n;
    while (l < r) {  // [l, r)
      int mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
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