
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
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  bool partitionArray(vector<int>& nums, const int K) {
    unordered_map<int, int> h;
    for (auto x : nums) {
      h[x]++;
    }
    max_queue<int> que;
    for (auto [k, v] : h) {
      que.push(v);
    }
    vector<int> buf;
    buf.reserve(K);
    while (!que.empty()) {
      while (buf.size() < K && !que.empty()) {
        buf.push_back(que.top());
        que.pop();
      }
      if (buf.size() < K) return false;
      for (auto freq : buf) {
        if (freq > 1) {
          que.push(freq - 1);
        }
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