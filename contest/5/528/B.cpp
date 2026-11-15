
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
  int n;
  vector<vector<int>> tree;
  vector<int> op;
  vector<int> score;
  int Dfs(int u) {
    if (tree[u].empty()) {
      return score[u];
    }
    int sum = score[u];
    int minVal = 0;
    bool first = true;
    for (int v : tree[u]) {
      int val = Dfs(v);
      sum += val;
      if (first) {
        minVal = val;
        first = false;
      } else {
        minVal = min(minVal, val);
      }
    }
    if (op[u] == 0) {
      if (minVal < 0) {
        sum -= minVal;
      } else {
        // do nothing
      }
    } else {
      sum -= minVal;
    }
    return sum;
  }

 public:
  int maxScore(vector<int>& parent, vector<int>& op_, vector<int>& score_) {
    op.swap(op_);
    score.swap(score_);
    n = parent.size();
    tree.resize(n);
    for (int i = 1; i < n; i++) {
      tree[parent[i]].push_back(i);
    }
    return Dfs(0);
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