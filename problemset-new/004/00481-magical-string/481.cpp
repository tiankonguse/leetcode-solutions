
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
  int magicalString(int n) {
    string s = "122";
    s.reserve(n);
    int l = 2;
    while (int(s.size()) < n) {
      char pre = s.back();
      if (pre == '2') {
        pre = '1';
      } else {
        pre = '2';
      }
      int v = s[l] - '0';
      while (v--) {
        s.push_back(pre);
      }
      l++;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        ans++;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(int n, const int& ans) {  //
  TEST_SMP1(Solution, magicalString, ans, n);
}

int main() {
  Test(6, 3);
  Test(1, 1);
  Test(6000, 2998);
  return 0;
}

#endif