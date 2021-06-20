#include "base.h"

class Solution {
 public:
  // 2 <= n <= 100000
  int findRepeatNumber(vector<int>& nums) {
    unordered_set<int> s;
    for (auto v : nums) {
      if (s.count(v) != 0) {
        return v;
      }
      s.insert(v);
    }

    return 0;
  }
};

int main() {
  TEST_SMP1(Solution, findRepeatNumber, 2, vector<int>({2, 3, 1, 0, 2, 5, 3}));

  return 0;
}