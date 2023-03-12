// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int splitNum(int num) {
    string str = to_string(num);
    sort(str.begin(), str.end());
    string a, b;
    for (int i = 0; i < str.size(); i++) {
      if (i) {
        a.push_back(str[i]);
      } else {
        b.push_back(str[i]);
      }
    }
    return atoi(a.c_str()) + atoi(b.c_str());
  }
};
