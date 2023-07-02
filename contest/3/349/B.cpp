// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string smallestString(string& s) {
    int flag = 0;
    for (auto& c : s) {
      if (flag == 0) {
        if (c == 'a') {
          continue;
        }
        flag = 1;
        c--;
      } else {
        if (c == 'a') {
          break;
        }
        c--;
      }
    }
    if(flag == 0){
      s.back() = 'z';
    }
    return s;
  }
};