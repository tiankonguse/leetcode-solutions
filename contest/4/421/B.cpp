// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
class Solution {
 public:
  int lengthAfterTransformations(const string& s, int t) {
    vector<ll> nums(27, 0);
    for (auto c : s) {
      nums[c - 'a']++;
    }
    while (t--) {
      for (int i = 25; i >= 0; i--) {
        nums[i + 1] = nums[i];
        nums[i] = 0;
      }
      nums[0] = (nums[0] + nums[26]) % mod;
      nums[1] = (nums[1] + nums[26]) % mod;
      nums[26] = 0;
    }
    ll ans = 0;
    for (auto v : nums) {
      ans = (ans + v) % mod;
    }
    return ans;
  }
};