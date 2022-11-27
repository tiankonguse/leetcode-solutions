#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Sum(int a, int b) { return (a + b) * (b - a + 1) / 2; }

 public:
  int pivotInteger(int n) {
    for (int i = 1; i <= n; i++) {
      if (Sum(1, i) == Sum(i, n)) return i;
    }
    return -1;
  }
  int pivotInteger1(int n) {
    int x = sqrt(n * (n + 1) / 2.0);
    if (x * x * 2 == n * (n + 1)) return x;
    return -1;
  }
};
