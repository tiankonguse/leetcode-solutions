// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  int StringToInt(const string& date) {
    int num = 0;
    for (auto c : date) {
      num = num * 10 + (c - '0');
    }
    return num;
  }
   string IntToBinary(int num) {
    string ret;
    while (num) {
      ret.push_back('0' + (num % 2));
      num = num / 2;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }

 public:
  string convertDateToBinary(const string& date) {
    //  0123456789
    // "2080-02-29"
    int year = StringToInt(date.substr(0, 4));
    int mon = StringToInt(date.substr(5, 2));
    int day = StringToInt(date.substr(8));
    myprintf("y=%d m=%d d=%d\n", year, mon, day);
    string ans;
    ans.append(IntToBinary(year));
    ans.push_back('-');
    ans.append(IntToBinary(mon));
    ans.push_back('-');
    ans.append(IntToBinary(day));
    return ans;
  }
};