
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
  int maxVowels(const string& s, int k) {
    string aeiou = "aeiou";
    set<char> h(aeiou.begin(), aeiou.end());
    int ans = 0;
    int num = 0;
    int n = s.length();
    for (int i = 0; i < n; i++) {
      if (h.count(s[i])) {  // 加入
        num++;
      }
      if (i + 1 < k) {  // 不够
        continue;
      }
      ans = max(ans, num);          // 更新答案
      if (h.count(s[i - k + 1])) {  // 出
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