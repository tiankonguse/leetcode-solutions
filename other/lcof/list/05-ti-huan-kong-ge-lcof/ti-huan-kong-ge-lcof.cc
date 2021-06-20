#include "base.h"

class Solution {
 public:
  string replaceSpace(string s) {
    string ans;
    for (auto c : s) {
      if (c == ' ') {
        ans.append("%20");
      } else {
        ans.push_back(c);
      }
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, replaceSpace, string("We%20are%20happy."),
            string("We are happy."));

  return 0;
}