
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
  vector<ll> prefixXor;
  void InitXor(const vector<int>& nums) {
    const int n = nums.size();
    prefixXor.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      if (mp.count(v) == 0) {
        mp[v] = Rand();
      }
      prefixXor[i] = prefixXor[i - 1] ^ mp[v];
    }
  }

  vector<tuple<int, int, int>> sortedQueries;  // <right, left, index>

  void InitQueries(const vector<vector<int>>& queries) {
    const int Q = queries.size();
    sortedQueries.reserve(Q);
    for (int i = 0; i < Q; i++) {
      auto& q = queries[i];
      sortedQueries.push_back({q[1] + 1, q[0] + 1, i});
    }
    sort(sortedQueries.begin(), sortedQueries.end());
  }

  vector<bool> ans;
  void Solver(const vector<int>& nums, const int K) {
    ans.resize(sortedQueries.size());
    const int n = nums.size();
    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      mp[v] = 0;  // 清空
    }

    auto Update = [&](const int i) {
      const int v = nums[i - 1];
      if (mp[v] != 0) {
        const int idx = mp[v];
        FenwickTree::bit_update(idx, -1);
      }
      mp[v] = i;
      FenwickTree::bit_update(i, 1);
    };

    const int Q = sortedQueries.size();
    int offset = 0;
    FenwickTree::bit_init(n);
    for (int i = 1; i <= n && offset < Q; i++) {
      Update(i);
      while (offset < Q && get<0>(sortedQueries[offset]) == i) {
        const auto [right, left, idx] = sortedQueries[offset];
        const int k = FenwickTree::bit_query(right) - FenwickTree::bit_query(left - 1);
        if (k == K && prefixXor[right] == prefixXor[left - 1]) {
          ans[idx] = true;
        }
        offset++;
      }
    }
  }

 public:
  vector<bool> validSubarrays(vector<int>& nums, int k, vector<vector<int>>& queries) {
    const int n = nums.size();
    InitXor(nums);
    InitQueries(queries);
    Solver(nums, k);
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