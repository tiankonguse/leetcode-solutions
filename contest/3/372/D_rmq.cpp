// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> leftmostBuildingQueries(vector<int>& heights,
                                      vector<vector<int>>& queries) {
    const int n = heights.size();
    const int qn = queries.size();
    vector<int> ans(qn, -1);

    vector<int> ansInedx(qn);
    for (int i = 0; i < qn; i++) {
      ansInedx[i] = i;
      auto& q = queries[i];
      if (q[0] > q[1]) {
        swap(q[0], q[1]);
      }
    }
    sort(ansInedx.begin(), ansInedx.end(), [&queries](int a, int b) {  //
      if (queries[a][1] == queries[b][1]) {
        return queries[a][0] > queries[b][0];
      }
      return queries[a][1] > queries[b][1];
    });

    vector<pair<int, int>> sta;
    sta.push_back({INT_MAX, n});
    for (const int index : ansInedx) {
      const auto& q = queries[index];
      const int a = q[0], b = q[1];  // a<=b

      if (a == b || heights[a] < heights[b]) {
        ans[index] = b;
        printf("q: a=%d b=%d index=%d ans=%d\n", a, b, index, ans[index]);
        continue;
      }

      // 更新单调栈
      while (b < sta.back().second) {
        const int i = sta.back().second - 1;
        const ll v = heights[i];
        while (v >= sta.back().first) {
          sta.pop_back();
        }
        sta.push_back({v, i});
      }

      // sta 递减序列
      const pair<int, int> v = {max(heights[a], heights[b]), INT_MAX};
      auto it = upper_bound(sta.rbegin(), sta.rend(), v);
      if (it->second == n) {
        ans[index] = -1;
      } else {
        ans[index] = it->second;
      }
      printf("q: a=%d b=%d index=%d ans=%d v=%d staSize=%d\n", a, b, index,
             ans[index], v.first, sta.size());
    }
    return ans;
  }
};