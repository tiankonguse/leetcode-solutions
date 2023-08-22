// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i + 1 < n; i++) {
      if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1]) return i;
    }
    return 0;
  }
};
