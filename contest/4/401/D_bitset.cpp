// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  int maxTotalReward(vector<int>& rewardValues) {
    sort(rewardValues.begin(), rewardValues.end());

    const size_t N = 10e5;
    bitset<N> flags;
    flags.set(0);
    for (auto v : rewardValues) {
      auto lowBit = flags << (N - v) >> (N - v);
      flags |= lowBit << v;
    }
    for (int i = N-1; i >= 0; i--) {
      if (flags.test(i)) {
        return i;
      }
    }

    return 0;
  }
};