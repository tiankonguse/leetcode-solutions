
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
class SnapshotArray {
  int snap_id = 0;
  unordered_map<int, vector<pair<int, int>>> H;
  int n;

 public:
  SnapshotArray(int length) { n = length; }

  void set(int index, int val) {
    if (H.count(index) == 0) {
      H[index].push_back({0, 0});
    }
    auto& h = H[index];
    if (h.back().first == snap_id) {
      h.back().second = val;
    } else {
      h.push_back({snap_id, val});
    }
  }

  int snap() {
    snap_id++;
    return snap_id - 1;
  }

  int get(int index, int snap_id) {
    if (H.count(index) == 0) {
      return 0;
    }
    auto& h = H[index];
    auto it = lower_bound(h.begin(), h.end(), pair<int, int>{snap_id + 1, 0});
    it--;
    return it->second;
  }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
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