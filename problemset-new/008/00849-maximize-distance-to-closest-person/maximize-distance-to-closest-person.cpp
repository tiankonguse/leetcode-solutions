/*************************************************************************
    > File Name: maximize-distance-to-closest-person.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月28日 19:22:28
 ************************************************************************/

#include <time.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "../../include/base.h"
using namespace std;

#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;

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

void test(vector<int>& data) {
  Solution work;
  int ans;
  ans = work.maxDistToClosest(data);
  output("data", data);
  output("ans", ans);
}

int main() {
  vector<int> data;

  data = {1, 0, 0, 0, 1, 0, 1};
  test(data);

  data = {1, 0, 0, 0};
  test(data);

  data = {0, 0, 0, 1};
  test(data);

  return 0;
}
