// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  string exp;
  void DfsBase(int& p, set<string>& ans) {
    ans.insert("");

    while (p < n) {
      if (exp[p] == '}') {
        break;
      } else if (exp[p] == '{') {
        set<string> tmp;
        p++;  // skip {
        DfsBase(p, tmp);
        p++;  // skip }
        printf("{}=%d ", tmp.size());
        for (auto& b : tmp) {
          printf("%s ", b.c_str());
        }
        printf("\n");

        set<string> s;
        for (auto& a : ans) {
          for (auto& b : tmp) {
            s.insert(a + b);
          }
        }
        ans.swap(s);
      } else if (exp[p] == ',') {
        set<string> tmp;
        p++;  // skip ,
        DfsBase(p, tmp);
        for (auto& a : tmp) {
          ans.insert(a);
        }

      } else {
        string str = ReadStr(p);
        set<string> tmp;
        for (auto& v : ans) {
          tmp.insert(v + str);
        }
        ans.swap(tmp);
      }
    }
  }
  string ReadStr(int& p) {
    string ans;
    while (p < n && exp[p] >= 'a' && exp[p] <= 'z') {
      ans.push_back(exp[p]);
      p++;
    }
    return ans;
  }

 public:
  vector<string> braceExpansionII(string exp_) {
    exp.swap(exp_);
    n = exp.size();
    set<string> ans;
    int p = 0;
    DfsBase(p, ans);
    return vector<string>(ans.begin(), ans.end());
  }
};