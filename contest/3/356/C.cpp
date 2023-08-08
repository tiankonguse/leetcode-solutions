// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  string ans;
  void Update(const string& a) {
    // printf("a=%s\n", a.c_str());
    if (a.length() < ans.length() || (a.length() == ans.length() && a < ans)) {
      ans = a;
    }
  }
  string f(const string& a, const string& b) {
    int an = a.length();
    int bn = b.length();

    string ret = a + b;

    for (int i = 0; i < an; i++) {
      int j = 0;
      for (j = 0; j < bn && i + j < an; j++) {
        if (a[i + j] != b[j]) {
          break;
        }
      }

      if (j == bn) {  // b 是 a 的子串
        ret = a;
        break;
      }
      if (i + j == an) {  // 找到最大匹配
        ret = a;
        while (j < bn) {
          ret.push_back(b[j]);
          j++;
        }
        break;
      }
    }
    // printf("a=%s b=%s ab=%s\n", a.c_str(), b.c_str(), ret.c_str());

    return ret;
  }
  void f3(const string& a, const string& b, const string& c) {
    Update(f(f(a, b), c));
  }

 public:
  string minimumString(const string& a, const string& b, const string& c) {
    ans = a + b + c;
    f3(a, b, c);
    f3(a, c, b);
    f3(b, a, c);
    f3(b, c, a);
    f3(c, a, b);
    f3(c, b, a);
    return ans;
  }
};
