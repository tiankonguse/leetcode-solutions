
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

// 988 / 999 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
  // 离散化，值域离散化到 [1,m]
  int m;
  void Init(vector<int>& nums) {
    unordered_map<int, int> mp;
    vector<int> sorted_nums = nums;
    sort(sorted_nums.begin(), sorted_nums.end());
    sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
    m = sorted_nums.size();
    for (int i = 1; i <= m; i++) {
      int v = sorted_nums[i - 1];
      mp[v] = i;
      sorted_nums[i - 1] = i;
    }
    for (auto& v : nums) {
      v = mp[v];
    }
  }
  ll ans = 0;
  void Dfs(vector<int>& nums, int lowVal, int highVal) {
    int n = nums.size();
    if (n < 2 || lowVal == highVal) return;

    int mid = (lowVal + highVal) / 2;
    vector<int> left, right;
    vector<int> lowSta;   // 单调递减栈(允许相等)
    vector<int> highSta;  // 单调递增栈(不允许相等)

    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      if (v <= mid) {
        while (!lowSta.empty() && nums[lowSta.back()] < v) {
          lowSta.pop_back();
        }
        lowSta.push_back(i);
        left.push_back(v);
      } else {
        while (!highSta.empty() && nums[highSta.back()] >= v) {
          highSta.pop_back();
        }
        if (highSta.empty()) {
          ans += lowSta.size();  // 不存在比 v 小的元素夹在 lowSta 与 v 之间
        } else {
          int last = highSta.back();
          ans += lowSta.end() - upper_bound(lowSta.begin(), lowSta.end(), last);
        }
        highSta.push_back(i);
        right.push_back(v);
      }
    }

    Dfs(left, lowVal, mid);
    Dfs(right, mid + 1, highVal);
  }

 public:
  ll shadowPairs(vector<int>& nums) {
    Init(nums);
    int n = nums.size();
    Dfs(nums, 1, m);
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