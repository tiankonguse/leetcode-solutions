
#include <bits/stdc++.h>

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
