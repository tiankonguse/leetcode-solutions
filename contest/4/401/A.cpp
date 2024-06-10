// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfChild(int n, int k) {
    int loop = k / (n - 1);
    int now = 1;
    int dir = 1;
    while (k--) {
      if (dir) {
        now++;
        if (now == n) {
          dir = 0;
        }
      } else {
        now--;
        if (now == 1) {
          dir = 1;
        }
      }
    }
    return now - 1;
  }
};