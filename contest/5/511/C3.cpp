#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<bool> transformStr(string s, vector<string>& strs) {
    int n = s.length();
    vector<int> pos_s;

    for (int i = 0; i < n; ++i) {
      if (s[i] == '0') {
        pos_s.push_back(i);
      }
    }

    int C = pos_s.size();
    vector<bool> ans;
    ans.reserve(strs.size());

    for (const string& p : strs) {
      int c0 = 0, cq = 0;

      for (char ch : p) {
        if (ch == '0')
          c0++;
        else if (ch == '?')
          cq++;
      }
      if (C < c0 || C > c0 + cq) {
        ans.push_back(false);
        continue;
      }

      int needed_q = C - c0;
      bool isValid = true;
      int j = 0;

      for (int i = 0; i < n; ++i) {
        if (p[i] == '0') {
          if (i > pos_s[j]) {
            isValid = false;
            break;
          }
          j++;
        } else if (p[i] == '?' && needed_q > 0) {
          if (i > pos_s[j]) {
            isValid = false;
            break;
          }
          j++;
          needed_q--;
        }
      }

      ans.push_back(isValid);
    }

    return ans;
  }
};