
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
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  int minSwaps(vector<int>& A, vector<int>& B) {
    int ans = 0;
    int n = A.size();
    unordered_map<int, int> H1;
    unordered_map<int, multiset<int>> H2;  // Av -> bv
    for (int i = 0; i < n; i++) {
      int a = A[i], b = B[i];
      if (a == b) {
        H1[a]++;
      } else {
        H2[a].insert(b);
      }
    }
    if (H1.empty()) return 0;

    max_queue<pair<int, int>> que;
    for (auto [val, cnt] : H1) {
      que.push({cnt, val});
    }
    while (que.size() >= 2) {
      auto [cnt1, val1] = que.top();
      que.pop();
      auto [cnt2, val2] = que.top();
      que.pop();

      H2[val1].insert(val2);
      H2[val2].insert(val1);
      cnt1--;
      cnt2--;
      if (cnt1 > 0) que.push({cnt1, val1});
      if (cnt2 > 0) que.push({cnt2, val2});
      ans++;
    }
    if (que.empty()) return ans;
    auto [cnt, val] = que.top();
    que.pop();

    for (auto& [av, bvList] : H2) {
      if (val == av) continue;
      for (auto bv : bvList) {
        if (bv != val) {
          ans++;
          cnt--;
          if (cnt == 0) return ans;
        }
      }
    }

    return -1;
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