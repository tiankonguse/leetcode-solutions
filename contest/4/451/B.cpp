
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
  string resultingString(const string& s) {
    string ans;
    ans.reserve(s.size());
    auto Check = [](char a, char b) {  //
      // 连续， a 与 b 也连续
      if (a > b) {
        swap(a, b);
      }
      return b - a == 1 || (b == 'z' && a == 'a');
    };
    for (auto c : s) {
      if (!ans.empty() && Check(c, ans.back())) {
        ans.pop_back();
      } else {
        ans.push_back(c);
      }
    }

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