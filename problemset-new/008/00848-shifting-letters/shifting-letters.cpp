/*************************************************************************
    > File Name: shifting-letters.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月28日 19:10:51
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

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;

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

void test(string s, vector<int>& data) {
  Solution work;
  string ans;
  ans = work.shiftingLetters(s, data);
  output("s", s);
  output("data", data);
  output("ans", ans);
}

int main() {
  string s;
  vector<int> data;

  s = "abc";
  data = {3, 5, 9};
  test(s, data);

  return 0;
}
