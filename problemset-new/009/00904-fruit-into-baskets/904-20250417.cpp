
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
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();
    int l = 0, r = 0;
    int ans = 0;
    unordered_map<int, int> m;
    auto updateRight = [&](int v) { m[v]++; };
    auto updateLeft = [&](int v) {
      m[v]--;
      if (m[v] == 0) {
        m.erase(v);
      }
    };
    auto shouldMoveLeft = [&]() -> bool { return m.size() > 2; };
    while (r < n) {
      int rv = fruits[r];
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (shouldMoveLeft()) {  // 第二步：移动左指针
        int lv = fruits[l];
        l++;
        updateLeft(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
    }
    return ans;
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