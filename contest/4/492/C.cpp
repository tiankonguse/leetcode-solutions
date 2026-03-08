
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
  int minOperations(const string s) {
    string S = s;
    map<char, int> cnt;
    for (char c : s) {
      cnt[c]++;
    }
    sort(S.begin(), S.end());
    if (S == s) {
      return 0;
    }
    if (S.size() == 2) {
      return -1;
    }
    if (S.front() == s.front() || S.back() == s.back()) {
      return 1;
    }
    char minVal = S.front();
    char maxVal = S.back();
    if (cnt[minVal] == 1 && cnt[maxVal] == 1 && s.front() == maxVal && s.back() == minVal) {
      return 3;
    }
    return 2;
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