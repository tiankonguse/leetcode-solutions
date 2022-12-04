#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isCircularSentence(string str) {
    char pre = str.back();
    if (str.front() != pre) return false;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == ' ') {
        if (str[i - 1] != str[i + 1]) return false;
      }
    }
    return true;
  }
};