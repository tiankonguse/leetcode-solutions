// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isAcronym(vector<string>& words, string s) {
    if (words.size() != s.size()) return false;
    for (int i = 0; i < s.size(); i++) {
      if (words[i].front() != s[i]) return false;
    }
    return true;
  }
};