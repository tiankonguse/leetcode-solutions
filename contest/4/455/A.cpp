
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
const int N = 110;
const int M = 110;
bool is[N];
int prm[M];
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
int getprm() {
  // O(n log log n)
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return k;
}

class Solution {
 public:
  bool checkPrimeFrequency(vector<int>& nums) {
    getprm();
    unordered_map<int, int> h;
    for (auto v : nums) {
      h[v]++;
    }
    for (auto [k, v] : h) {
      if (is[v]) return true;
    }
    return false;
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