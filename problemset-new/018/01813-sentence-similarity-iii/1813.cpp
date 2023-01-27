// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  void Split(const string& s, vector<string>& vec) {
    string tmp;
    for (auto c : s) {
      if (c == ' ') {
        if (!tmp.empty()) {
          vec.push_back(tmp);
          tmp.clear();
        }
      } else {
        tmp.push_back(c);
      }
    }
    if (!tmp.empty()) {
      vec.push_back(tmp);
      tmp.clear();
    }
  }

  vector<string> a, b;
  int an, bn;
  bool EqBack(int k) {
    for (int i = an - 1, j = bn - 1; k > 0; k--, i--, j--) {
      if (a[i] != b[j]) return false;
    }
    return true;
  }
  bool EqFront(int k) {
    for (int i = 0, j = 0; k > 0; k--, i++, j++) {
      if (a[i] != b[j]) return false;
    }
    return true;
  }
  bool Check() {
    // 枚举插入位置
    an = a.size();
    bn = b.size();

    for (int i = 0; i <= an; i++) {
      // 插入在第 i 个之前
      if (EqFront(i) && EqBack(an - i)) {
        return true;
      }
    }

    return false;
  }

 public:
  bool areSentencesSimilar(const string& s1, const string& s2) {
    Split(s1, a);
    Split(s2, b);

    if (a.size() > b.size()) {
      swap(a, b);
    }

    return Check();
  }
};
