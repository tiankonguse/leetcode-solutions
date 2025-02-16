
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

/*
执行用时分布 11ms 击败 93.52%
消耗内存分布 221.66MB 击败 74.69%
*/

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
const int N = 1e5 + 2;
class Solution {
 public:
  vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
    int maxVal = groups.front();
    for (auto v : groups) {
      maxVal = max(maxVal, v);
    }
    vector<int> G(maxVal + 1, N);
    int en = elements.size();
    for (int i = 0; i < en; i++) {
      int v = elements[i];
      if(v > maxVal) continue;
      if (G[v] != N) continue;
      for (int j = v; j <= maxVal; j += v) {
        G[j] = min(G[j], i);
      }
    }
    vector<int> ans;
    ans.reserve(groups.size());
    for (auto v : groups) {
      if (G[v] == N) {
        ans.push_back(-1);
      } else {
        ans.push_back(G[v]);
      }
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