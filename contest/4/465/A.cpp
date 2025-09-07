
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
  vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
    int n = order.size();
    vector<int> flag(n+1, 0);
    for (auto f : friends) {
      flag[f] = 1;
    }
    vector<int> res;
    res.reserve(friends.size());
    for (auto id : order) {
      if (flag[id]) {
        res.push_back(id);
      }
    }
    return res;
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