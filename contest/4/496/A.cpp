
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
  char getMirror(char c) {
    if (c >= '0' && c <= '9') {
      c = '9' - c + '0';
    } else {
      c = 'z' - c + 'a';
    }
    return c;
  }

 public:
  int mirrorFrequency(const string& s) {
    unordered_map<char, int> freq;
    for (auto c : s) {
      freq[c]++;
    }
    int ans = 0;
    unordered_set<char> visited;
    for (auto c : s) {
      if (visited.find(c) != visited.end()) {
        continue;
      }
      char mirror = getMirror(c);
      visited.insert(c);
      visited.insert(mirror);
      ans += abs(freq[c] - freq[mirror]);
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