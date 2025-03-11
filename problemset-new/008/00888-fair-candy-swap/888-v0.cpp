
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
  vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
    ll suma = 0, sumb = 0;
    for (auto v : aliceSizes) suma += v;
    for (auto v : bobSizes) sumb += v;

    ll sum = (suma + sumb) / 2;
    unordered_set<int> ha = {aliceSizes.begin(), aliceSizes.end()};
    unordered_set<int> hb = {bobSizes.begin(), bobSizes.end()};

    for (auto va : ha) {
      int vb = sum - (suma - va);
      if (hb.count(vb)) return {va, vb};
    }
    return {};
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