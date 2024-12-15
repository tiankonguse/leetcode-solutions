
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 5010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 53;

ll h[max3];
ll qpowCache[max3];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

void Init(const vector<int>& str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] + 1)) % mod1e7;
    h[i] = pre;
  }
}

class Solution {
 public:
  int beautifulSplits(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();

    Init(nums, n);
    // 子数组 nums1 是子数组 nums2 的前缀 或者 nums2 是 nums3 的前缀。
    for (int i = 0; i < n; i++) {  // 枚举 [0,i] [i+1, j] [j+1,n-1]
      for (int j = i + 1; j + 1 < n; j++) {
        int leftNum = i - 0 + 1;
        int midNum = j - (i + 1) + 1;
        int rightNum = n - 1 - (j + 1) + 1;
        if (leftNum <= midNum && H(0, i) == H(i + 1, i + 1 + leftNum - 1)) {
          ans++;
          continue;
        }
        if (midNum <= rightNum && H(i + 1, j) == H(j + 1, j + 1 + midNum - 1)) {
          ans++;
          continue;
        }
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

#endif©leetcode