// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll matrixSumQueries(int n, vector<vector<int>>& queries) {
    ll rowNum = 0;
    ll colNum = 0;

    unordered_set<int> rowFlag;
    unordered_set<int> colFlag;

    ll ans = 0;
    for (int i = queries.size() - 1; i >= 0; i--) {
      int type = queries[i][0];
      int index = queries[i][1];
      ll val = queries[i][2];

      if (type == 0) {  // 行
        if (rowFlag.count(index)) continue;
        ans += val * (n - colNum);
        rowNum++;
        rowFlag.insert(index);
      } else {  // 列
        if (colFlag.count(index)) continue;
        ans += val * (n - rowNum);
        colNum++;
        colFlag.insert(index);
      }
    }
    return ans;
  }
};