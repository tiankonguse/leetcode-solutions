// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minChanges(int n, int k) {
    if ((n & k) != k) return -1;
    return __builtin_popcount(n ^ k);
  }
};
