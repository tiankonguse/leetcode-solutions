// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumTimeToInitialState(const string& word, int k) {
    int n = word.length();
    const char* p = word.data();
    for (int i = 1; i * k < n; i++) {
      int offset = i * k;
      int len = n - offset;
      if (strncmp(p, p + offset, len) == 0) {
        return i;
      }
    }
    return (n + k - 1) / k;
  }
};