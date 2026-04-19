/*
数位 DP

常见问题：计算区间 `[l,r]` 中满足某些条件的整数个数。
基本思路：分别计算出 `[0,r]` 和 `[0,l-1]` 中满足某些条件的整数个数，然后相减即可。
关键算法：从高位到低位，枚举每一位的值，标记是否是上界，然后递归计算下一位。


模板有两个：
模板1：分别求 `[0,r]` 和 `[0,l-1]` 中满足条件的整数个数。
模板2：直接求 `[l,r]` 中满足条件的整数个数。
*/

namespace DfsR {

string s;
ll cache[17][11][2];
ll Dfs(int pos, int preSelectVal, bool limit) {
  if (pos == 16) {
    return 1; // 出口
  }
  if (cache[pos][preSelectVal][limit] != -1) {
    return cache[pos][preSelectVal][limit];
  }
  int up = limit ? s[pos] - '0' : 9;
  ll ret = 0;
  for (int val = 0; val <= up; val++) {
    if (IsInpath[pos]) {
      // 路径上的点，必须大于等于前一个点的值
      if (val >= preSelectVal) {
        ret += Dfs(pos + 1, val, limit && val == up);
      }
    } else { 
      // 非路径上的点，都可以选择
      ret += Dfs(pos + 1, preSelectVal, limit && val == up);
    }
  }
  return cache[pos][preSelectVal][limit] = ret;
}
ll Solver(ll x) {
  memset(cache, -1, sizeof(cache));
  return Dfs(0, 0, true);
}

ll ans = Solver(r) - Solver(l - 1);
}


namespace DfsLR {
string SL, SR;
ll cache[17][11][2][2];
ll Dfs(int pos, int preSelectVal, bool limitDown, bool limitUp) {
  if (pos == 16) {
    return 1;
  }
  if (cache[pos][preSelectVal][limitDown][limitUp] != -1) {
    return cache[pos][preSelectVal][limitDown][limitUp];
  }
  int down = limitDown ? SL[pos] - '0' : 0;
  int up = limitUp ? SR[pos] - '0' : 9;
  ll ret = 0;
  for (int val = down; val <= up; val++) {
    if (IsInpath[pos]) {
      if (val >= preSelectVal) {
        ret += Dfs(pos + 1, val, limitDown && val == down, limitUp && val == up);
      }
    } else {
      ret += Dfs(pos + 1, preSelectVal, limitDown && val == down, limitUp && val == up);
    }
  }
  return cache[pos][preSelectVal][limitDown][limitUp] = ret;
}
ll ans = Dfs(0, 0, true, true);
};