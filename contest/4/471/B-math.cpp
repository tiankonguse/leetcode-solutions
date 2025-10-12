
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


    int ans = 1;
    for (int i = 0; i < n; i++) {
      fill(freq.begin(), freq.end(), 0);
      int maxFreq = 0;
      int charCount = 0;

      for (int j = i; j < n; j++) {
        int v = s[j] - 'a';
        freq[v]++;
        if(freq[v] == 1) charCount++;
        maxFreq = max(maxFreq, freq[v]);
        if (maxFreq * charCount == (j - i + 1)) {
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