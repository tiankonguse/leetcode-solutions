// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findMinimumOperations(string s1, string s2, string s3) {
    int p = 0;
    int n1 = s1.size();
    int n2 = s2.size();
    int n3 = s3.size();
    while (p < n1 && p < n2 && p < n3) {
      if (s1[p] == s2[p] && s2[p] == s3[p]) {
        p++;
        continue;
      }
      break;
    }
    if (p == 0) {
      return -1;
    }
    return n1 + n2 + n3 - 3 * p;
  }
};