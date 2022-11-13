#include "base.h"

class Solution {
  string Phone(const string& s) {
    string num;
    for (auto v : s) {
      if (v >= '0' && v <= '9') {
        num.push_back(v);
      }
    }

    string ans;
    int n = num.size();
    if (n > 10) {
      ans.resize(n - 10 + 1, '*');
      ans[0] = '+';
      ans.push_back('-');
    }
    ans.append("***-***-");
    ans.append(num.substr(n - 4, 4));

    return ans;
  }
  string Email(string s) {
    string ans;

    for (auto& c : s) {
      if (c >= 'A' && c <= 'Z') {
        c = c - 'A' + 'a';
      }
    }
    auto it = s.find('@');

    ans.resize(7, '*');
    ans.front() = s[0];
    ans.back() = s[it - 1];
    ans.append(s.substr(it));

    return ans;
  }

 public:
  string maskPII(string s) {
    if (s.find('@') == string::npos) {
      return Phone(s);
    } else {
      return Email(s);
    }
  }
};
