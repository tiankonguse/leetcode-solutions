#include "base.h"

class Solution {
 public:
  bool CheckPermutation(string s1, string s2) {
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
  }
};

int main() {
  TEST_SMP2(Solution, CheckPermutation, true, string("abc"), string("bca"));
  TEST_SMP2(Solution, CheckPermutation, false, string("abc"), string("bad"));

  return 0;
}