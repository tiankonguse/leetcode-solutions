// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool squareIsWhite(const string& v) {
    return ((v[0] - 'a') + (v[1] - '0')) % 2;
  }
};
