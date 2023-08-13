// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  int maxDistToClosest(vector<int>& seats) {
    int ans = 0;
    int tmpans = 0;
    int nowZero = 0;

    int state = 0;  //
    for (int index = 0; index < seats.size(); index++) {
      if (seats[index] == 1) {
        if (state == 0) {
          //处理前缀0
          tmpans = nowZero;
          state = 1;
        } else {
          //中间状态
          tmpans = (nowZero + 1) / 2;
        }
        if (tmpans > ans) {
          ans = tmpans;
        }
        nowZero = 0;
      } else {
        nowZero++;
        if (index + 1 == seats.size()) {
          //后缀0
          if (nowZero > ans) {
            ans = nowZero;
          }
        }
      }
    }

    return ans;
  }
};