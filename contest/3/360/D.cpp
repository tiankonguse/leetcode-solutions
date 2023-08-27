// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  // 反向图
  vector<vector<int>> g;
  // 0 未访问 1 初次访问 2 非环上节点 3 环上节点(指向环所在数组)
  vector<int> flag;
  unordered_map<int, vector<ll>> h;  // 第几个环
  int loopNum = 0;
  vector<pair<int, int>> loopPos;  // [loopNum, loopIndex]
  ll ans = 0;

  vector<ll> tmpSum;
  ll K;
  void Dfs(int loopIn, int p) {
    ll tmpAns = 0;
    ll tmpK = K;
    if (p != loopIn) {
      int tmpNum = tmpSum.size() - 1;
      if (tmpNum <= tmpK) {
        tmpAns += tmpSum.back();
        tmpK -= tmpNum;
      } else {
        int r = tmpNum;
        int l = r - tmpK;
        tmpAns += tmpSum[r] - tmpSum[l];
        tmpK = 0;
      }
    }
    if (tmpK > 0) {
      auto [loopNum, loopIndex] = loopPos[loopIn];
      auto& vecSum = h[loopNum];
      ll vecNum = vecSum.size() - 1;
      tmpAns += vecSum.back() * (tmpK / vecNum);
      tmpK %= vecNum;
      if (tmpK > 0) {
        int l = loopIndex;
        int r = vecNum;
        if (r - l + 1 < tmpK) {
          tmpK -= r - l + 1;
          tmpAns += vecSum[r] - vecSum[l - 1];

          if (tmpK > 0) {
            l = 1;
            r = l + tmpK - 1;
            tmpAns += vecSum[r] - vecSum[l - 1];
            tmpK = 0;
          }
        } else {
          r = l + tmpK - 1;
          tmpAns += vecSum[r] - vecSum[l - 1];
          tmpK = 0;
        }
      }
    }
    ans = max(ans, tmpAns);
    for (auto pp : g[p]) {
      if (flag[pp] != 2) continue;
      tmpSum.push_back(tmpSum.back() + pp);
      Dfs(loopIn, pp);
      tmpSum.pop_back();
    }
  }

 public:
  long long getMaxFunctionValue(vector<int>& nums_, long long k) {
    nums.swap(nums_);
    K = k + 1;
    // printf("next\n");
    int n = nums.size();
    g.resize(n);
    for (int i = 0; i < n; i++) {
      int p = nums[i];
      g[p].push_back(i);
    }

    loopPos.resize(n, {-1, -1});
    flag.resize(n, 0);
    for (int i = 0; i < n; i++) {
      if (flag[i]) continue;
      int p = i;
      while (flag[p] == 0) {
        flag[p] = 1;
        p = nums[p];
      }

      if (flag[p] == 1) {  // 新的环
        loopNum++;
        auto& vecSum = h[loopNum];
        vecSum.push_back(0);
        while (flag[p] == 1) {
          flag[p] = 3;
          vecSum.push_back(vecSum.back() + p);
          loopPos[p] = {loopNum, vecSum.size() - 1};
          p = nums[p];
        }
      }
      // 其余是非环上节点
      p = i;
      while (flag[p] == 1) {
        flag[p] = 2;
        p = nums[p];
      }
    }

    for (int i = 0; i < n; i++) {
      if (flag[i] == 3) {
        tmpSum.clear();
        tmpSum.push_back(0);
        Dfs(i, i);
      }
    }

    return ans;
  }
};