// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  // 0 0 => 0 0
  // 0 1 => 1 1
  // 1 0 => 1 1
  // 1 1 => 1 0
  // 结论1：使用一个 1，可以将另外一个数字反转。
  // 结论2：一对 01 可以转化为 11
 public:
  bool makeStringsEqual(const string& s, const string& t) {
    if (s == t) return true;
    bool a = s.find('1') != std::string::npos;
    bool b = t.find('1') != std::string::npos;
    return a && b;
  }
};

