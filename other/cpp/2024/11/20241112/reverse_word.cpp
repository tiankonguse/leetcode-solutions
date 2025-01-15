#include <bits/stdc++.h>
using namespace std;
const int N = 200;
char s1[N], s2[N];
char temp[N][N];
int main() {
  char c;
  int wi, wj, p, q;
  wi = wj = 0;
  while (c = getchar()) {
    if (c == ' ') {
      temp[wi++][wj] = '\0';
      wj = 0;
    }
    if (c == '\n') {
      temp[wi++][wj] = '\0';
      wj = 0;
      break;  // 这里要跳出循环
    } else {
      temp[wi][wj++] = c;
    }
  }

  scanf("%s", s1);
  scanf("%s", s2);
  for (p = 0; p < wi; p++) {
    if (strcmp(s1, temp[p]) == 0) {
      strcpy(temp[p], s2);  // 替换
    }
  }
  for (p = 0; p < wi; p++) {
    printf("%s", temp[p]);
    printf(" ");
  }
  printf("\n");
  return 0;
}