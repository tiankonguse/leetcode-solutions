// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long putMarbles(vector<int>& weights, int k) {
    int n = weights.size();

    vector<ll> dis(n - 1);
    for (int i = 0; i + 1 < n; i++) {
      dis[i] = weights[i] + weights[i + 1];
    }
    sort(dis.begin(), dis.end());
    ll minVal = weights.front() + weights.back();
    for (int i = 0; i < k-1; i++) {
      minVal += dis[i];
    }

    ll maxVal = weights.front() + weights.back();
    std::reverse(dis.begin(), dis.end());
    for (int i = 0; i < k-1; i++) {
      maxVal += dis[i];
    }
    return maxVal - minVal;
  }
};