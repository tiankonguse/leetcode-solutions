
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
  bool canMakeSubsequence(const string& s, const string& t) {
    int ns = s.size();
    int nt = t.size();
    if (ns > nt) return false;
    if(ns == 1) return true;
    vector<int> prefix(ns + 1, nt);
    for (int ti = 0, si = 0; ti < nt; ti++) {
      if (si < ns && s[si] == t[ti]) {
        prefix[si + 1] = ti;
        si++;
      }
    }
    vector<int> suffix(ns + 1, -1);
    for (int ti = nt - 1, si = ns - 1; ti >= 0; ti--) {
      if (si >= 0 && s[si] == t[ti]) {
        suffix[si] = ti;
        si--;
      }
    }
    for (int si = 0; si < ns; si++) {  // 枚举替换的位置
      if (si == 0) {
        if (suffix[si + 1] > 0) return true;
      } else if (si == ns - 1) {
        if (prefix[si] < nt - 1) return true;
      } else {
        if (prefix[si] + 1 < suffix[si + 1]) return true;
      }
    }
    return false;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif