
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
  int minDeletion(const string& s, int k) {
    unordered_map<char, int> cnt;
    for (char c : s) {
      cnt[c]++;
    }
    vector<pair<int, char>> freq;
    for (auto& [c, v] : cnt) {
      freq.push_back({v, c});
    }
    sort(freq.begin(), freq.end());
    std::reverse(freq.begin(), freq.end());
    int ans = 0;
    while (freq.size() > k) {
      ans += freq.back().first;
      freq.pop_back();
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