
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

namespace FenwickTree {
// 树状数组 (BIT) 的最大尺寸
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
// O(log N) 查找排名第 K 的元素
// 使用二分查找在 BIT 上定位
int find_kth(int k) {
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

};  // namespace FenwickTree

class Solution {
  ll Rand() {
    // 随机生成一个 64 位的随机数
    return rand() | ((ll)rand() << 32);
  }
  unordered_map<int, ll> mp;
  vector<tuple<int, int, int>> sortedQueries;  // <right, left, index>

  vector<bool> moQueAns;
  void InitMoQueue(vector<int>& nums, int k, vector<vector<int>>& queries) {
    int n = nums.size();
    int BLOCK_SIZE = sqrt(n) + 1;  // 每个组的大小
    sortedQueries.clear();
    for (int i = 0; i < queries.size(); i++) {
      sortedQueries.emplace_back(queries[i][0], queries[i][1], i);
    }
    sort(sortedQueries.begin(), sortedQueries.end(), [&](const auto& a, const auto& b) {
      auto [a_left, a_right, a_idx] = a;
      auto [b_left, b_right, b_idx] = b;

      int block_l_a = a_left / BLOCK_SIZE;
      int block_l_b = b_left / BLOCK_SIZE;

      if (block_l_a != block_l_b) {
        return block_l_a < block_l_b;
      }
      // 奇偶优化 (Mo's odd-even optimization)
      if (block_l_a % 2 == 0) {
        return a_right < b_right;
      } else {
        return a_right > b_right;
      }
    });

    for (auto v : nums) mp[v] = 0;

    int current_cnt = 0;  // 元素偶数个的个数
    auto Add = [&](int v) {
      mp[v]++;
      if (mp[v] % 2 == 0) {
        current_cnt++;  // 变成偶数
      } else {
        current_cnt--;  // 变成奇数
      }
    };
    auto Remove = [&](int v) {
      mp[v]--;
      if (mp[v] % 2 == 0) {
        current_cnt++;  // 变成偶数
      } else {
        current_cnt--;  // 变成奇数
      }
    };

    moQueAns.resize(queries.size());
    int current_l = 0, current_r = -1;
    // [left, right]
    for (auto& [left, right, index] : sortedQueries) {
      while (current_l > left) Add(nums[--current_l]);
      while (current_l < left) Remove(nums[current_l++]);
      while (current_r < right) Add(nums[++current_r]);
      while (current_r > right) Remove(nums[current_r--]);
      moQueAns[index] = current_cnt == 0;
    }
  }

  vector<int> firstK, secnodK;
  vector<int> InitRange(const vector<int>& nums, const int K) {
    int n = nums.size();
    mp.clear();

    vector<int> left(n);
    int l = 0;
    for (int i = 0; i < n; i++) {
      mp[nums[i]]++;
      while (mp.size() >= K) {
        mp[nums[l]]--;
        if (mp[nums[l]] == 0) {
          mp.erase(nums[l]);
        }
        l++;
      }
      left[i] = l;
    }
    return left;
  }

 public:
  vector<bool> validSubarrays(vector<int>& nums, int k, vector<vector<int>>& queries) {
    const int n = nums.size();
    InitMoQueue(nums, k, queries);
    firstK = InitRange(nums, k + 1);
    secnodK = InitRange(nums, k);

    vector<bool> ans;
    ans.reserve(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      auto& query = queries[i];
      int left = query[0], right = query[1];
      if (!moQueAns[i]) {
        ans.push_back(false);
        continue;
      }
      if (firstK[right] <= left && left < secnodK[right]) {
        ans.push_back(true);
      } else {
        ans.push_back(false);
      }
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