
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
struct SlideWindow {
  string name;
  unordered_map<int, int> cnt;
  int kNum = 0;
  int validNum = 0;
  int R = -1;
  const int K;
  const int M;
  SlideWindow(const string& name,int k, int m) : name(name),K(k), M(m) {
    kNum = 0;
    validNum = 0;
    R = -1;
  }
  int OK() { return kNum == K && validNum == K; }
  int Right() { return R; }
  int Next() { return R + 1; }
  void Add(int val, int r) {
    if (R >= r) return;
    this->R = r;
    cnt[val]++;
    if (cnt[val] == 1) {
      kNum++;
    }
    if (cnt[val] == M) {
      validNum++;
    }
  }
  void Remove(int val) {
    cnt[val]--;
    if (cnt[val] == 0) {
      kNum--;
    }
    if (cnt[val] == M - 1) {
      validNum--;
    }
  }
};
class Solution {
 public:
  long long countSubarrays(vector<int>& nums, int k, int m) {
    int n = nums.size();
    SlideWindow swMin("min", k, m);
    SlideWindow swMax("max", k, m);
    long long ans = 0;
    for (int i = 0; i < n; i++) {  // 左边界为 i
      swMin.Add(nums[i], i);
      swMax.Add(nums[i], i);
      while ((swMin.kNum < k || swMin.kNum == k && swMin.validNum < k) && swMin.Next() < n) {
        swMin.Add(nums[swMin.Next()], swMin.Next());
      }
      if (swMin.OK()) {
        while (swMax.kNum <= k && swMax.Next() < n) {
          swMax.Add(nums[swMax.Next()], swMax.Next());
        }
        if (swMax.OK()) {
          ans += swMax.Right() - swMin.Right() + 1;
        } else {
          ans += swMax.Right() - swMin.Right();
        }
      }
      swMin.Remove(nums[i]);
      swMax.Remove(nums[i]);
    }
    return ans;
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