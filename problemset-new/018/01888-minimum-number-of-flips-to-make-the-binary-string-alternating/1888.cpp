
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  // 思路：操作1等价与循环数组，相等于窗口为 n，枚举起始位置分别为0/1 时需要修改的次数
  int minFlips(const string& s) {
    int n = s.size();
    int ans = n;
    int num = 0;  // 假设其实位置为 0
    for (int i = 0; i < n * 2 - 1; i++) {
      int v = s[i % n] - '0';
      if (v != (i & 1)) {
        num++;
      }
      if (i < n - 1) continue;
      ans = min(ans, min(n - num, num));
      v = s[(i - n + 1) % n] - '0';
      if (v != ((i - n + 1) & 1)) {
        num--;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif