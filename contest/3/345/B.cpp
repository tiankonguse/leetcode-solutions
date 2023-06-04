// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Check(vector<int>& derived, bool firstVal) {
    int n = derived.size();
    vector<int> ans(n, 0);
    ans[0] = firstVal;
    for (int i = 1; i < n; i++) {
      ans[i] = ans[i - 1] ^ derived[i - 1];
    }
    return (ans.back() ^ ans.front()) == derived.back();
  }

 public:
  bool doesValidArrayExist(vector<int>& derived) {
    return Check(derived, 0) || Check(derived, 1);
  }
};