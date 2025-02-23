#include <bits/stdc++.h>
using namespace std;
int main() {
  char a[1001][1001];
  char str[1001];
  int max_ct = 0;
  int index = 0;
  int re[1001] = {0};
  int p = 0;
  int n;  // 字符串的长度
  while (scanf("%s", str) != EOF) {
    n = strlen(str);
    strcpy(a[index++], str);
    for (int i = 0; i < n; i++) {
      re[p] |= 1 << (str[i] - 'a');
    }
    p++;
  }
  for (int i = 0; i < index - 1; i++) {
    for (int j = i + 1; j < index; j++) {
      if ((re[i] & re[j]) == 0) {
        max_ct = max(max_ct, strlen(a[i]) * strlen(a[j]));
      }
    }
  }
  printf("%d\n", max_ct);
  return 0;
}