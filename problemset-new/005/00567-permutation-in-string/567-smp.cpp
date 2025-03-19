
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
  bool checkInclusion(const string& s1, const string& s2) {
    int n = s2.size();
    int k = s1.size();
    if (k > n) {
      return false;
    }
    unordered_map<char, int> h;
    for (auto c : s1) {
      h[c]++;
    }
    for (int i = 0; i < n; i++) {
      h[s2[i]]--;
      if (h[s2[i]] == 0) {
        h.erase(s2[i]);
      }
      if (i < k - 1) {
        continue;
      }
      if (h.empty()) {
        return true;
      }
      h[s2[i - k + 1]]++;
      if (h[s2[i - k + 1]] == 0) {
        h.erase(s2[i - k + 1]);
      }
    }
    return false;
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