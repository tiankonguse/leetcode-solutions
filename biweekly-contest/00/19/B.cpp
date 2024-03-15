// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    int n = arr.size();

    ll sum = 0;
    for (int i = 0; i < k - 1; i++) {
      sum += arr[i];
    }

    int ans = 0;
    for (int i = k - 1; i < n; i++) {
      sum += arr[i];
      if (sum >= threshold * k) {
        ans++;
      }
      sum -= arr[i - k + 1];
    }
    return ans;
  }
};