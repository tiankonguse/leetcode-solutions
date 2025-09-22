
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
const int base[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};
int vis[1000000];
class Solution {
  pair<int, int> Init(vector<int>& nums1, vector<int>& nums2) {  // 值域离散化 [1,6]
    unordered_map<int, int> h;
    int index = 0;
    for (auto v : nums1) {
      if (!h.count(v)) {
        ++index;
        h[v] = index;
      }
    }
    int start = 0;
    for (auto& v : nums1) {
      start = start * 10 + h[v];
    }
    int target = 0;
    for (auto& v : nums2) {
      target = target * 10 + h[v];
    }
    return {start, target};
  }

 public:
  int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {  //
    int n = nums1.size();
    auto [start, target] = Init(nums1, nums2);
    MyPrintf("start=%d target=%d\n", start, target);
    if (start == target) return 0;

    queue<int> que;
    memset(vis, 0, sizeof(vis));
    auto Add = [&](int v, int step) {
      if (vis[v]) return;
      que.push(v);
      vis[v] = step;
    };
    Add(start, 1);
    while (!que.empty()) {
      const int v = que.front();
      que.pop();
      int step = vis[v];
      for (int l = 0; l < n; l++) {  // [l, mid) [mid, r)
        for (int mid = l + 1; mid < n; mid++) {
          for (int r = mid + 1; r <= n; r++) {
            const int lm = mid - l, lr = r - mid;
            const int lowVal = v % base[mid] / base[l];
            const int highVal = v % base[r] / base[mid];
            const int newVal = v - lowVal * base[l] - highVal * base[mid] + lowVal * base[l + lr] + highVal * base[l];
            if (newVal > base[6]) {
              MyPrintf("newVal=%d l=%d mid=%d r=%d, [l,mid)=%d [mid,r)=%d\n", newVal, l, mid, r, mid - l, r - mid);
              MyPrintf("base[l]=%d base[mid]=%d base[r]=%d\n", base[l], base[mid], base[r]);
              MyPrintf("lowVal=%d highVal=%d\n", lowVal, highVal);
            }
            Add(newVal, step + 1);
            if (newVal == target) {
              return step;
            }
          }
        }
      }
    }
    return 0;
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