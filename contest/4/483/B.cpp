
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
  vector<vector<string>> wordSquares(vector<string>& words) {
    int n = words.size();
    vector<vector<string>> ans;
    // top, left, right, bottom
    // top[0] == left[0], top[3] == right[0]
    // bottom[0] == left[3], bottom[3] == right[3]
    for (int top = 0; top < n; top++) {
      for (int left = 0; left < n; left++) {
        if (top == left) continue;
        if (words[top][0] != words[left][0]) continue;
        for (int right = 0; right < n; right++) {
          if (right == top || right == left) continue;
          if (words[top][3] != words[right][0]) continue;
          for (int bottom = 0; bottom < n; bottom++) {
            if (bottom == top || bottom == left || bottom == right) continue;
            if (words[left][3] != words[bottom][0]) continue;
            if (words[right][3] != words[bottom][3]) continue;
            vector<string> tmp;
            tmp.push_back(words[top]);
            tmp.push_back(words[left]);
            tmp.push_back(words[right]);
            tmp.push_back(words[bottom]);
            ans.push_back(tmp);
          }
        }
      }
    }
    sort(ans.begin(), ans.end());
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