// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Check(const string& s1, const string& s2) {
    int num = 0;
    for (int i = 0; i < s1.size(); i++) {
      if (s1[i] <= s2[i]) {
        num++;
      }
    }
    return num == s1.size();
  }

 public:
  bool checkIfCanBreak(string s1, string s2) {
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return Check(s1, s2) || Check(s2, s1);
  }
};