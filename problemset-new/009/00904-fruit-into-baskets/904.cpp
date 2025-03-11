
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
  int totalFruit(vector<int>& fruits) {
    int ans = 0;
    int n = fruits.size();
    int l = 0, r = 0;
    unordered_map<int, int> m;
    while (r < n) {  // [l, r)
      m[fruits[r]]++;
      r++;
      while (m.size() > 2) {
        m[fruits[l]]--;
        if (m[fruits[l]] == 0) {
          m.erase(fruits[l]);
        }
        l++;
      }
      ans = max(ans, r - l);
    }
    return ans;
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