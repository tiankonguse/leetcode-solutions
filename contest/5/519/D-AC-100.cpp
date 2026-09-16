
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

class FenwickTree {
  // 树状数组 (BIT) 的最大尺寸
 public:
  vector<int> BIT;
  int n;

  void bit_init(int n_) {
    n = n_;
    BIT.resize(n + 1);
    fill(BIT.begin(), BIT.end(), 0);
  }

  void bit_update(int idx, int delta) {
    for (; idx <= n; idx += idx & -idx) {
      BIT[idx] += delta;
    }
  }

  int bit_query(int idx) {  // 查询 [1, idx] 的总数
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
      sum += BIT[idx];
    }
    return sum;
  }
  // O(log N) 查找排名第 K 的元素 (即中位数)
  // 使用二分查找在 BIT 上定位
  int find_kth(int k, int median_val) {
    if (k <= 0) return median_val;
    int low = 1, high = n;
    int median = n;

    // 经典二分查找
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (bit_query(mid) >= k) {
        median = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return median;
  }
};

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
    FenwickTree ft;
    ft.bit_init(n);
    vector<int> lowSta;   // 单调递减栈(允许相等)
    vector<int> highSta;  // 单调递增栈(不允许相等)

    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      if (v <= mid) {
        while (!lowSta.empty() && nums[lowSta.back()] < v) {
          int last = lowSta.back();
          lowSta.pop_back();
          ft.bit_update(last + 1, -1);
        }
        lowSta.push_back(i);
        ft.bit_update(i + 1, 1);
        left.push_back(v);
      } else {
        while (!highSta.empty() && nums[highSta.back()] >= v) {
          highSta.pop_back();
        }
        if (highSta.empty()) {
          ans += lowSta.size();  // 不存在比 v 小的元素夹在 lowSta 与 v 之间
        } else {
          int last = highSta.back();
          // 求区间 [last, i] 的区间和
          ans += ft.bit_query(i + 1) - ft.bit_query(last + 1);
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