#include "base.h"

class Solution {
 public:
  bool isUnique(string astr) {
    unordered_set<char> s;
    for (auto c : astr) {
      if (s.count(c)) {
        return false;
      }
      s.insert(c);
    }
    return true;
  }
};

int main() {
  TEST_SMP1(Solution, isUnique, false, string("leetcode"));
  TEST_SMP1(Solution, isUnique, true, string("abc"));

  return 0;
}