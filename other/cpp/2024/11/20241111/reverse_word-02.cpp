#include <bits/stdc++.h>
using namespace std;
const int N = 501;
char s[N][N];
void rev(char t[]) {  // 注意保留空格
  int i = 0;
  int j;
  int right = 0;  // 右边端点
  while (t[i] != ' ') {
    right++;
    i++;
    if (right == strlen(t))  // 最后一个字符跳出循环
      break;
  }
  for (i = 0, j = right - 1; i < j; i++, j--) {
    swap(t[i], t[j]);
  }
}
int main() {
  int flag = 1;
  int i, j, k, q;
  i = j = 0;
  char c;
  while ((c = getchar()) != '\n') {
    if (c == ' ') {
      flag = 1;
      s[i][j] = ' ';  // 保留空格
      j++;            // 多个空格都要存进去
    } else {
      if (flag == 1) {
        i++;
        j = 0;
        flag = 0;
      }
      s[i][j] = c;
      j++;
    }
  }
  s[i][j] = '\0';
  /*for(k=1;k<=i;k++){
   for(q=0;q<strlen(s[k]);q++){//这里直接写小于它的长度即可
    printf("%c",s[k][q]);
   }
   printf("\n");
  }
  */

  for (k = 1; k <= i; k++) {
    rev(s[k]);
  }
  for (k = 1; k <= i; k++) {
    for (q = 0; q < strlen(s[k]); q++) {  // 这里直接写小于它的长度即可
      printf("%c", s[k][q]);
    }
  }
  printf("\n");

  return 0;
}