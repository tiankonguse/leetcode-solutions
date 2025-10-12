
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
  int longestBalanced(const string& s) {
    int n = s.size();
    vector<int> freq(26, 0);
    unordered_map<int, int> counts;

    auto Add = [&](int v) {
      if (freq[v] > 0) {
        int c = freq[v];
        counts[c]--;
        if (counts[c] == 0) counts.erase(c);
        freq[v]++;
        counts[freq[v]]++;
      } else {
        freq[v] = 1;
        counts[freq[v]]++;
      }
    };

    int ans = 1;
    for (int i = 0; i < n; i++) {
      fill(freq.begin(), freq.end(), 0);
      counts.clear();
      for (int j = i; j < n; j++) {
        int v = s[j] - 'a';
        Add(v);
        if (counts.size() == 1) {
          ans = max(ans, j - i + 1);
        }
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