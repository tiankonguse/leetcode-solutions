// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  char minVal;
  char maxVal;
  int n;

  bool Check(string& s, int i) {
    // 第 i 位设置为 s[i]，是否合法尚未判断
    if (i >= 1 && s[i - 1] == s[i]) return false;  // 长度为 2 的回文串
    if (i >= 2 && s[i - 2] == s[i]) return false;  // 长度为 3 的回文串
    return true;
  }

 public:
  string smallestBeautifulString(string s, int k) {
    minVal = 'a';
    maxVal = minVal + k - 1;

    n = s.length();
    for (int i = n - 1; i >= 0; i--) {  // 枚举第几位开始变大的
      for (char c = s[i] + 1; c <= maxVal; c++) {  // 枚举变大的具体字符值
        s[i] = c;
        if (Check(s, i)) {
          // k>=4, 之后肯定存在答案,
          for (int j = i + 1; j < n; j++) {
            for (char c = minVal; c <= maxVal; c++) { // 实际上只会遍历前 3 个字符即可贪心出答案
              s[j] = c;
              if(Check(s, j)) break;
            }
          }
          return s;
        }
      }
    }
    return "";
  }
};