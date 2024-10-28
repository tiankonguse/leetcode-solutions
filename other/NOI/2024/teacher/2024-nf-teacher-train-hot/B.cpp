#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*
10110111
17

10001

*/

char str[1111];
char ans[1111];

int main() {
  scanf("%s", str);
  int n = strlen(str);
  std::reverse(str, str + n);
  // printf("reverse=  %s\n", str);
  str[n++] = '0';  // 高位补充一个 0，避免进位

  // printf("append 0 =%s\n", str);

  for (int i = 0; i < 4; i++) {
    ans[i] = '0';      // 右移 4 位， ans 低位补充 4 个 0
    str[n + i] = '0';  // 右移 4 位， str 高位补充 4 个 0
  }

  for (int i = 0; i < n; i++) {
    ans[i + 4] = str[i];
  }
  n = n + 4;
  ans[n] = '\0';
  str[n] = '\0';
  // printf("befor str=%s\n", str);
  // printf("befor ans=%s\n", ans);

  // ans = ans + str
  int pre = 0;
  for (int i = 0; i < n; i++) {
    int a = ans[i] - '0';
    int b = str[i] - '0';
    pre = pre + a + b;
    ans[i] = '0' + (pre % 2);
    pre = pre / 2;
  }
  // printf("after ans=%s\n", ans);
  while (n > 1 && ans[n - 1] == '0') {
    ans[n - 1] = '\0';
    n--;
  }
  std::reverse(ans, ans + n);
  printf("%s\n", ans);

  return 0;
}