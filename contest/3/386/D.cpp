// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Ok(vector<int>& flag, int mid) {
    int sum = 0;
    for (int offset = mid; offset >= 1; offset--) {
      if (flag[offset]) {
        sum++;
        ll dis = mid - offset + 1;
        if (sum * 2 > dis) return false;
      }
    }
    return true;
  }

 public:
  int earliestSecondToMarkIndices(const vector<int>& nums,
                                  const vector<int>& changeIndices) {
    const int n = nums.size();

    auto Check = [&](const int mid) -> bool {  // 下标从 1 开始
      map<ll, int> h;                          // changeIndices 中的下标
      for (int offset2 = mid; offset2 >= 1; offset2--) {
        const int offset1 = changeIndices[offset2 - 1];
        const ll val1 = nums[offset1 - 1];
        if (val1 <= 1) continue;
        h[offset1] = offset2;
      }
      vector<pair<ll, int>> vals;  // {nums 中的值 与 下标}
      vals.reserve(h.size());
      for (auto [offset1, offset2] : h) {
        ll val1 = nums[offset1 - 1];
        vals.push_back({val1, offset1});
      }
      sort(vals.begin(), vals.end(),
           [](const auto& a, const auto& b) { return a.first > b.first; });

      vector<int> flag2(mid + 1, 0);
      unordered_set<int> flag1;
      ll insert_num = 0;

      for (auto [val1, offset1] : vals) {
        int offset2 = h[offset1];
        flag2[offset2] = 1;

        if (Ok(flag2, mid)) {  // 可以插入
          insert_num++;
          flag1.insert(offset1);
        } else {
          flag2[offset2] = 0;
        }
      }

      ll left_sum = 0;
      for (int offset1 = 1; offset1 <= n; offset1++) {
        if (flag1.count(offset1)) continue;
        left_sum += nums[offset1 - 1];
      }

      printf("mid=%d insert_num=%d left_sum=%lld n=%d ans=%d\n", mid,
             insert_num, left_sum, n, insert_num + left_sum + n <= mid);
      return insert_num + left_sum + n <= mid;
    };

    const int m = changeIndices.size();
    int l = 1, r = m + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (r == m + 1) return -1;
    return r;
  }
};

/*
[ 9, 8, 7, 3, 9, 9, 2, 6, 8 ,1 ,0 ,4 ,4]
 01 02 03 04 05 06 07 08 09 10 11 12 13
 00 00 00 00 00 00    00 00       00 00

 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
[09,07,13,10,01,03,01,03,02,03,05,07,11,05,13,02,01,13,12,08,06,09,04,06,05,11,10,6,12,4,9,1,13,10,1,8,4,9,5,3,7,12,7,7]
 00    00    00 00       00    00                      00 00 00
*/