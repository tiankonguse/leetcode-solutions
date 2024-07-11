// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string getEncryptedString(const string& s, int k) {
    int n = s.size();
    k = k % n;
    if (k == 0) {
      return s;
    } else {
      return s.substr(k) + s.substr(0, k);
    }
  }
};
