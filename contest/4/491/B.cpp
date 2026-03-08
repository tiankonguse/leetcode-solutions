
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
  vector<int> dp;
  int dfs(int n){
    int& ret = dp[n];
    if (ret != -1) return ret;
    if(n == 1 || n == 2){
      return ret = n - 1;
    }
    ret = 1*(n-1) + dfs(1) + dfs(n-1);
    for(int i = 2; i < n; i++){
      ret = min(ret, i * (n - i) + dfs(i) + dfs(n - i));
    }
    return ret;
  }
public:
    int minCost(int n) {
        dp.resize(n + 100, -1);
        dp[1] = 0;
        dp[2] = 1;
        return dfs(n);
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