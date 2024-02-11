// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 3;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

void Init(const int* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + str[i]) % mod1e7;
    h[i] = pre;
  }
}
class Solution {
 public:
  int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
    int n = nums.size();
    for (int i = 0; i + 1 < n; i++) {
      if (nums[i] > nums[i + 1]) {
        nums[i] = 0;
      } else if (nums[i] < nums[i + 1]) {
        nums[i] = 2;
      } else {
        nums[i] = 1;
      }
    }
    nums.back() == 0;

    ll patternHash = 0;
    for (auto& v : pattern) {
      v++;
      patternHash = (patternHash * BASE + v) % mod1e7;
    }

    int m = pattern.size();
    Init(nums.data(), n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (i + m - 1 >= n - 1) break;
      if (H(i, i + m - 1) == patternHash) {
        ans++;
      }
    }
    return ans;
  }
};