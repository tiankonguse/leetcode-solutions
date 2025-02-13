
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
// GCD 相关算法

// 推论1：有俩个数p,q,且gcd(q,p)=1,则最大无法表示成px+qy（x>=0,y>=0)的数是pq-q-p.

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}

/*
1 1 1 1
2 1 1 -> C(4,2)
2 2 -> C(4,2)
3 1 -> C(4,3)
4
*/
class Solution {
  int ans = INT_MAX;
  map<int, int> h;
  int n;
  int tmpAns = 0;

  vector<int> target;
  void Dfs(const int p, ll lcm) {
    for (int i = 0; i <= p; i++) {
      ll v = target[i];
      // 选择第 i 个
      swap(target[i], target[p]);
      ll newLcm = lcm / gcd(lcm, v) * v;
      


      swap(target[i], target[p]);
    }
  }

 public:
  int minimumIncrements(vector<int>& nums, vector<int>& target_) {
    target.swap(target_);
    for (auto v : nums) {
      h[v]++;
    }

    n = target.size();
    Dfs(n - 1, 1);
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