/*
描述
输入一个字符串，以回车结束（字符串长度<=100）。
该字符串由若干个单词组成，单词之间用一个空格隔开，所有单词区分大小写。现需要将其中的某个单词替换成另一个单词，并输出替换之后的字符串。
输入
输入包括3行，
第1行是包含多个单词的字符串 s;
第2行是待替换的单词a(长度 <= 100);
第3行是a将被替换的单词b(长度 <= 100).

s, a, b 最前面和最后面都没有空格.
输出
输出只有 1 行，将s中所有单词a替换成b之后的字符串。
样例输入
You want someone to help you
You
I
样例输出
I want someone to help you


解题方法：
char 字符数组
string 数组
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 200;
char s1[N], s2[N];
char temp[N][N];
int main() {
  char c;
  int wi, wj, p;
  wi = wj = 0;
  while ((c = getchar())) {
    if (c == ' ') {
      temp[wi++][wj] = '\0';
      wj = 0;
      break;
    }
    if (c == '\n') {
      temp[wi++][wj] = '\0';
      wj = 0;
      break;  // ’‚¿Ô“™Ã¯≥ˆ—≠ª∑
    } else {
      temp[wi][wj++] = c;
    }
  }

  scanf("%s", s1);
  scanf("%s", s2);
  for (p = 0; p < wi; p++) {
    if (strcmp(s1, temp[p]) == 0) {
      strcpy(temp[p], s2);  // ÃÊªª
    }
  }
  for (p = 0; p < wi; p++) {
    printf("%s", temp[p]);
    printf(" ");
  }
  printf("\n");
  return 0;
}
