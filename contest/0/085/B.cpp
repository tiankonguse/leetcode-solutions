// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string pushDominoes(string str) {
    int preRight = -1;  // 第一个 R
    int n = str.size();
    for (int i = 0; i < n; i++) {
      if (str[i] == 'L') {
        if (preRight == -1) {
          int r = i - 1;
          while (r >= 0 && str[r] == '.') {
            str[r] = 'L';
            r--;
          }
        } else {
          int r = i - 1;
          int l = preRight + 1;
          while (l < r) {
            str[l] = 'R';
            str[r] = 'L';
            l++;
            r--;
          }
          preRight = -1;
        }
      } else if (str[i] == 'R') {
        if (preRight != -1) {
          int l = preRight + 1;
          while (l < i) {
            str[l] = 'R';
            l++;
          }
        }
        preRight = i;
      } else {  // str[i] == "."
      }
    }
    if (preRight != -1) {
      int l = preRight + 1;
      while (l < n) {
        str[l] = 'R';
        l++;
      }
    }
    return str;
  }
};
