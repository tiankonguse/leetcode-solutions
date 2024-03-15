// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> replaceElements(vector<int>& arr) {
    int maxVal = -1;
    std::reverse(arr.begin(), arr.end());
    for (auto& v : arr) {
      swap(maxVal, v);
      maxVal = max(maxVal, v);
    }
    std::reverse(arr.begin(), arr.end());
    return arr;
  }
};
