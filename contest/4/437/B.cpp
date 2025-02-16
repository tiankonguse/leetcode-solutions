
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
  ll maxWeight(vector<int>& pizzas) {
    sort(pizzas.begin(), pizzas.end());
    ll ans = 0;
    int n = pizzas.size();
    int day = n / 4;
    int l = 0, r = n - 1;
    for (int i = 1; i <= day; i += 2) {  // 奇数天，选择1个最大，3个最小
      ans += pizzas[r];
      r -= 1;
      l += 3;
    }
    for (int i = 2; i <= day; i += 2) {  // 偶数天，选择 2 个最大，2个最小
      ans += pizzas[r - 1];
      r -= 2;
      l += 2;
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