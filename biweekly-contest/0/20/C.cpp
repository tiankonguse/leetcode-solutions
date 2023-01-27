// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSubstrings(const string& s) {
    ll n = s.size();
    vector<int> nums(3, 0);

    ll ans = 0;
    int l = 0, r = 0;
    while (l < n) {
      while (r < n && !(nums[0] && nums[1] && nums[2])) {
        nums[s[r] - 'a']++;
        r++;
      }

      if (nums[0] && nums[1] && nums[2]) {
        ans += n - r + 1;
      }
      nums[s[l] - 'a']--;
      l++;
    }

    return ans;
  }
};
