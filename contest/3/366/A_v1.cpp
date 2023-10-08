// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int Sum(int n) { return (1 + n) * n / 2; }
  int differenceOfSums(int n, int m) {
    int num2 = Sum(n / m) * m;
    int num1 = Sum(n) - num2;
    return num1 - num2;
  }
};