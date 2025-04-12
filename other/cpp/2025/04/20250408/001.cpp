/*
【题目描述】
李莳花要做一个架子，把她喜欢的摆件叠放起来，她的每个摆件的位置顺序是固定的。这个架子的宽度是
W，每层排放的摆件不能超过这个宽度，每层架子的高度不能低于最高的摆件的高度。假设，给出排列好的每个摆件的宽度 Wi ，和高度
Hi ，请计算需要最少多高的架子。

【输入格式】
输入的第一行有 2 个数字，一个是摆件的个数n，和架子的宽度 W。 以下摆件个数 n 行，每行的第一个数是摆件的宽度 Wi 和高度
Hi。

【输出格式】
输出放置摆件架子的最低高度。

【样例输入】(测试数据不包含本样例)
5 5
2 1
1 2
1 3
2 3
2 2

【样例输出】
5
*/

#include <bits/stdc++.h>
using namespace std;
const int maxnum = 1000;
int dp[maxnum];  // 状态：前i个花盆所需的最低架子的高度
int wid[maxnum];
int heg[maxnum];  // 存储每个花盆的宽度和高度
int n, w;         // 花盆的个数和每层最大宽度
int main() {
  scanf("%d%d", &n, &w);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &wid[i], &heg[i]);
  }
  // 初始值
  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;  // 边界值，不放花盆时高度为0
  int width;  // 计算花盆的总宽度
  int high;   // 计算一层中花盆的最高高度
  // 状态转移核心
  for (int i = 1; i <= n; i++) {
    width = 0;                      // 计算花盆的总宽度
    high = 0;                       // 计算一层中花盆的最高高度
    for (int j = i; j >= 1; j--) {  // dp的数组都是1到n ，数组都是0到n-1
      width += wid[j - 1];
      if (width > w) {
        break;
      }
      high = max(high, heg[j - 1]);  // 更新花盆的最高高度
      dp[i] = min(dp[i], dp[j - 1] + high);
    }
  }
  printf("%d", dp[n]);

  return 0;
}