// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int maximizeSquareArea(int m, int n, vector<int>& hFences,
                         vector<int>& vFences) {
    hFences.push_back(1);
    hFences.push_back(m);
    sort(hFences.begin(), hFences.end());

    vFences.push_back(1);
    vFences.push_back(n);
    sort(vFences.begin(), vFences.end());
    unordered_set<ll> hash;
    for (int i = 0; i < vFences.size(); i++) {
      for (int j = i + 1; j < vFences.size(); j++) {
        ll dis = vFences[j] - vFences[i];
        hash.insert(dis);
      }
    }

    int hm = hFences.size();
    ll ans = -1;
    for (int i = 0; i < hm; i++) {
      for (int j = i + 1; j < hm; j++) {
        ll dis = hFences[j] - hFences[i];
        if (hash.count(dis)) {
          ans = max(ans, dis);
        }
      }
    }
    if (ans != -1) {
      ans = (ans * ans) % mod;
    }
    return ans;
  }
};