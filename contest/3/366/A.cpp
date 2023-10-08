// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int differenceOfSums(int n, int m) {
    int num1 = 0;
    int num2 = 0;
    for (int i = 1; i <= n; i++) {
      if (i % m != 0) {
        num1 += i;
      } else {
        num2 += i;
      }
    }
    return num1 - num2;
  }
};