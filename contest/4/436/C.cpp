
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

/*
执行用时分布 2364ms 击败 21.67%
消耗内存分布 525.15MB 击败 7.76%
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
class Solution {
 public:
  ll countSubstrings(const string& s) {
    ll ans = 0;
    for (int i = 1; i < 10; i++) {
      vector<int> pre(i, 0);

      for (auto c : s) {
        const int v = c - '0';
        vector<int> tmp(i, 0);
        tmp[v % i]++;
        for (int j = 0; j < i; j++) {
          const int V = (j * 10 + v) % i;
          tmp[V] += pre[j];
        }
        if (v == i) {
          ans += tmp[0];
        }
        printf("v=%d\n", v);
        for (int j = 0; j < i; j++) {
          printf("i=%d j=%d num=%d\n", i, j, tmp[j]);
        }
        pre = std::move(tmp);
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