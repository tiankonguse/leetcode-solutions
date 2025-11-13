
#include <bits/stdc++.h>
int nextt[];

void get_next1(string &t) {
  int n = t.length();
  nextt[0] = -1;  // fix: next[0] = 0
  // 计算 next[1] 到 next[n-1]
  for (int j = 1; j < n; j++) {
    int k = nextt[j - 1];  // j-1位置的最长公共前后缀长度

    while (k > 0 && t[k] != t[j]) {
      k = nextt[k];
    }
    if (t[k] == t[j]) {
      nextt[j] = k + 1;
    }
  }
}

void get_next(string &t) {
  int m = t.length();
  nextt[0] = -1;  // 初始条件
  int k = -1;
  int j = 0;
  // 计算 next[1] 到 next[m-1]
  while (j < m) {                   // 状态转移方程
    if (k == -1 || t[j] == t[k]) {  // 当匹配时
      nextt[++j] = ++k;
    }
    // 当不匹配时，根据next数组回退k的位置
    else {
      k = nextt[k];
    }
  }
}

// （1）如果tk==tj时，则next[j+1]=next[j]+1=k+1;
// （2）如果tk!=tj时，则对这两个字符串进行匹配，回退到k’=next[k]的位置，比较tk’和tj是否相等。
// （3）重复步骤1,2，当回退到第0个字符时停止，此时next[j+1]=0.(边界条件）
