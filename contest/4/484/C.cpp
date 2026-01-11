
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
  ll countPairs(vector<string>& words) {
    unordered_map<string, int> mp;
    ll ans = 0;
    for (auto& word : words) {
      int m = word.size();
      int shift = 'z' - word[0];
      for (int i = 0; i < m; i++) {
        word[i] = (word[i] - 'a' + shift) % 26 + 'a';
      }
      ans += mp[word];
      mp[word]++;
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