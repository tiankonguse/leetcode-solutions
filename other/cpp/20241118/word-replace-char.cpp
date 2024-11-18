#include <bits/stdc++.h>
using namespace std;
const int N = 200;
char str[N], s1[N], s2[N];
char temp[N][N];
int main() {
  cin.getline(str, 200);
  scanf("%s", s1);
  scanf("%s", s2);
  int n = strlen(str);
  int i, wi, wj, p, q;
  wi = wj = 0;
  for (i = 0; i < n; i++) {
    if (str[i] == ' ' || str[i] == '\0') {
      temp[wi][wj] = '\0';
      wi++;
      wj = 0;
    } else {
      temp[wi][wj] = str[i];
      wj++;
    }
  }

  for (p = 0; p < i; p++) {
    if (strcmp(s1, temp[p]) == 0) {
      strcpy(temp[p], s2);
    }
  }
  for (p = 0; p < i; p++) {
    printf("%s", temp[p]);
    printf(" ");
  }
  printf("\n");
  return 0;
}
