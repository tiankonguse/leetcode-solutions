
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
class RangeFreqQuery {
  unordered_map<int, vector<int>> m;

 public:
  RangeFreqQuery(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
      m[arr[i]].push_back(i);
    }
  }

  int query(int left, int right, int value) {
    if (m.count(value) == 0) {
      return 0;
    }
    auto& h = m[value];
    auto it1 = lower_bound(h.begin(), h.end(), left);
    auto it2 = upper_bound(h.begin(), h.end(), right);
    return it2 - it1;
  }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif