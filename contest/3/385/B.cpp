// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
    vector<pair<string, int>> arr;
    arr.reserve(arr1.size() + arr2.size());
    for (auto v : arr1) {
      arr.emplace_back(make_pair<string, int>(to_string(v), 0));
    }
    for (auto v : arr2) {
      arr.emplace_back(make_pair<string, int>(to_string(v), 1));
    }
    sort(arr.begin(), arr.end());

    int ans = 0;
    for (int i = 1; i < arr.size(); i++) {
      auto& [av, ai] = arr[i - 1];
      auto& [bv, bi] = arr[i];
      if (ai != bi) {
        int abi = min(av.size(), bv.size());
        int tmpAns = abi;
        for (int i = 0; i < abi; i++) {
          if (av[i] != bv[i]) {
            tmpAns = i;
            break;
          }
        }
        ans = max(ans, tmpAns);
      }
    }

    return ans;
  }
};
