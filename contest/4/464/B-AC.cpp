
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  bool partitionArray(vector<int>& nums, const int K) {
    unordered_map<int, int> h;
    for (auto x : nums) {
      h[x]++;
    }
    map<int, int> h2;
    for (auto [k, v] : h) {
      h2[-v]++;
    }
    for (auto [freq, count] : h2) {
      MyPrintf("freq=%d, count=%d\n", freq, count);
    }
    vector<int> buf;
    buf.reserve(K);
    while (!h2.empty()) {
      MyPrintf("begin h2.size=%d\n", int(h2.size()));
      for (auto& [freq, count] : h2) {
        while (buf.size() < K && count > 0) {
          buf.push_back(freq);
          count--;
        }
        if (buf.size() == K) {
          MyPrintf("bufSize=%d freq=%d count=%d\n", int(buf.size()), freq, count);
          break;
        }
      }
      MyPrintf("bufSize=%d \n", int(buf.size()));
      if (buf.size() < K) return false;
      for (auto freq : buf) {
        if (h2.count(freq) != 0 && h2[freq] == 0) {
          h2.erase(freq);
        }
        if (freq + 1 != 0) {
          h2[freq + 1]++;
        }
      }
      for (auto [freq, count] : h2) {
        MyPrintf("next freq=%d, count=%d\n", freq, count);
      }
      buf.clear();
    }
    return true;
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