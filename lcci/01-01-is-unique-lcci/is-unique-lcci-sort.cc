#include "base.h"

class Solution {
 public:
  bool isUnique(string str) {
    sort(str.begin(), str.end());
    for (int i = 1; i < str.size(); i++) {
      if (str[i] == str[i - 1]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  TEST_SMP1(Solution, isUnique, false, string("leetcode"));
  TEST_SMP1(Solution, isUnique, true, string("abc"));

  return 0;
}