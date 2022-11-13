#include "base.h"

typedef long long ll;
class Solution {
 public:
  int uniqueLetterString(const string& s) {
    int n = s.length();
    vector<int> pre(26, -1);
    vector<int> nums(n, -1);

    for (int i = 0; i < n; i++) {
      int v = s[i] - 'A';
      nums[i] = pre[v];
      pre[v] = i;
    }

    ll ans = 0;
    for (int i = 0; i < 26; i++) {
      int now = n;
      int p = pre[i];
      while (p != -1) {
        ans += (now - p) * (p - nums[p]);
        now = p;
        p = nums[p];
      }
    }
    return ans;
  }
};