
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

class TimeMap {
  unordered_map<string, vector<pair<int, string>>> H;

 public:
  TimeMap() {}

  void set(string key, string value, int timestamp) { H[key].push_back({timestamp, value}); }

  string get(string key, int timestamp) {
    if (H.count(key) == 0) {
      return "";
    }
    auto& h = H[key];
    auto it = lower_bound(h.begin(), h.end(), pair<int, string>{timestamp + 1, ""});
    if (it == h.begin()) {
      return "";
    }
    it--;
    return it->second;
  }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

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