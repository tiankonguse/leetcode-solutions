
// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string compressedString(const string& word) {
    string ans;
    ans.reserve(word.size() * 2);

    int preNum = 0;
    char preVal = ' ';
    for (auto c : word) {
      if (c == preVal) {
        preNum++;
        if (preNum == 9) {
          ans.push_back('0' + preNum);
          ans.push_back(preVal);
          preVal = ' ';
          preNum = 0;
        }
      } else {
        if (preNum > 0) {
          ans.push_back('0' + preNum);
          ans.push_back(preVal);
        }
        preVal = c;
        preNum = 1;
      }
    }
    if (preNum > 0) {
      ans.push_back('0' + preNum);
      ans.push_back(preVal);
    }
    return ans;
  }
};