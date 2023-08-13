// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string shiftingLetters(string s, vector<int>& shifts) {
    int sum = 0;
    for (int i = shifts.size() - 1; i >= 0; i--) {
      sum += shifts[i];
      sum %= 26;
      s[i] = 'a' + (((s[i] - 'a') + sum) % 26);
    }
    return s;
  }
};