
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
template <class T>
void chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
}
class Solution {
 public:
  int minimumCardPickup(vector<int>& cards) {
    unordered_map<int, int> m;
    int ans = -1;
    for (int i = 0; i < cards.size(); i++) {
      int v = cards[i];
      if (m.count(v)) {
        chmin(ans, i - m[v] + 1);
      }
      m[v] = i;
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