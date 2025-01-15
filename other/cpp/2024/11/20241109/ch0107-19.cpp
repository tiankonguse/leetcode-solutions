// http://noi.openjudge.cn/ch0107/19/

// 问题: i 循环的时候，里面的逻辑修改 i
#include <bits/stdc++.h>
using namespace std;
const int N = 32;
char s[N], t[N];
int main() {
  scanf("%s%s", s, t);
  int n, m;
  n = strlen(s);
  m = strlen(t);
  if (n < m) swap(s, t);  // 交换两个字符串
  n = strlen(s);          // 重新求长度
  m = strlen(t);
  // printf("%s%s",s,t);
  int i, j;  // 表示连个字符串对比的初始位置
  int flag;
  for (i = 0; i < n; i++) {
    j = 0;  // 每次都从头开始匹配
    flag = 1;
    while (j < m) {  // 当没有到达短字符串的末尾，我就一直比对
      // printf("s[%d]=%c s[%d]=%c\n",i,s[i],j,t[j]);
      if (s[i] == t[j]) {
        i = (i + 1) % n;  // 因为字符会移位
        j++;
      } else {
        flag = 0;
        break;  // 说明从当前位置无法匹配，从下一个位置开始。
      }
    }
    if (j == m) {  // 说明找到一个子串了，就退出
      break;
    }
  }
  if (flag == 1)
    printf("true\n");
  else
    printf("false\n");
  return 0;
}