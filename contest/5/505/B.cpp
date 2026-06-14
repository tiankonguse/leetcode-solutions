
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
  vector<string> generateValidStrings(int n, int k) {  //
    vector<string> ans;
    ans.reserve(1 << n);
    string s;
    function<void(int, int)> dfs = [&](int i, int cost) {
      if (i == n) {
        if (cost <= k) ans.push_back(s);
        return;
      }
      s.push_back('0');
      dfs(i + 1, cost);
      s.pop_back();
      if (s.empty() || s.back() == '0') {
        s.push_back('1');
        dfs(i + 1, cost + i);
        s.pop_back();
      }
    };
    dfs(0, 0);
    return ans;
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