// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool checkPowersOfThree(int n) {
    vector<ll> pows3;
    ll base = 1;
    while (base <= n) {
      pows3.push_back(base);
      base = base * 3;
    }

    for (int i = pows3.size() - 1; i >= 0; i--) {
      if (n >= pows3[i]) {
        n -= pows3[i];
      }
    }
    return n == 0;
  }
};
