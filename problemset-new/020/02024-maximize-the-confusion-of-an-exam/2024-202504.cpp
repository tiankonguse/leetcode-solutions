
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int maxConsecutiveAnswers(const string& answerKey, const int k) {
    auto Solver = [&](char c) -> int {
      int n = answerKey.size();
      int l = 0, r = 0;
      int num = 0;
      int ans = 0;
      auto updateRight = [&](char v) {
        if (v == c) num++;
      };
      auto updateLeft = [&](char v) {
        if (v == c) num--;
      };
      auto shouldMoveLeft = [&](char rv) -> bool { return num > k; };
      while (r < n) {
        char rv = answerKey[r];
        r++;
        updateRight(rv);  // 第一步：移动右指针

        while (shouldMoveLeft(rv)) {  // 第二步：移动左指针
          char lv = answerKey[l];
          l++;
          updateLeft(lv);
        }

        ans = max(ans, r - l);  // 第三步：更新答案
      }
      return ans;
    };
    return max(Solver('T'), Solver('F'));
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif