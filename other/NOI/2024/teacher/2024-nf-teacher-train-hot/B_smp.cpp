#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*
10110111
17

10001

*/

char str[1111];

int main() {
  scanf("%s", str);
  int n = strlen(str);
  std::reverse(str, str + n);
  for (int i = 0; i < 6; i++) {
    str[n++] = '0';  // 乘 17 等价于 A<<4 + A，最多进位 5 位
  }

  str[n] = '\0';
  int pre = 0;
  for (int i = 0; i < n; i++) {
    int a = str[i] - '0';
    pre = pre + a * 17;
    str[i] = '0' + (pre % 2);
    pre = pre / 2;
  }
  while (n > 1 && str[n - 1] == '0') {
    str[n - 1] = '\0';
    n--;
  }
  std::reverse(str, str + n);
  printf("%s\n", str);

  return 0;
}