#include "base.h"

class Solution {
 public:
  bool isUnique(string astr) {
    uint8_t m[256];
    memset(m, 0, sizeof(m));
    for (uint8_t c : astr) {
      if (m[c]) {
        return false;
      }
      m[c]++;
    }
    return true;
  }
};

int main() {
  TEST_SMP1(Solution, isUnique, false, string("leetcode"));
  TEST_SMP1(Solution, isUnique, true, string("abc"));

  return 0;
}