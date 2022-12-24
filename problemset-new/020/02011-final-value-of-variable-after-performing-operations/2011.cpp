// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int finalValueAfterOperations(vector<string>& operations) {
    int ans = 0;
    for (auto& s : operations) {
      if (s[1] == '+') {
        ans++;
      } else {
        ans--;
      }
    }
    return ans;
  }
};