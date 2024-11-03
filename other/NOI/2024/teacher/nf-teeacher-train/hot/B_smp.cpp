#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*
11 * 17 = 17

第0位：17%2 = 1， 进位 17/2 = 8
第1位：8%2  = 0， 进位 8/2  = 4
第2位：4%2  = 0，

10001

*/

char str[1111];

int main() {
  scanf("%s", str);
  int n = strlen(str);
  // 第一步：翻转
  std::reverse(str, str + n);

  // 第二步：高位补0
  for (int i = 0; i < 6; i++) { // 补 0 法
    str[n++] = '0';  // 乘 17 等价于 A<<4 + A，最多进位 5 位
  }

  // 第三步计算
  str[n] = '\0';
  int pre = 0;
  for (int i = 0; i < n; i++) {
    const int a = str[i] - '0';
    pre = pre + a * 17;
    str[i] = '0' + (pre % 2);
    pre = pre / 2;
  }

  // 第四步：删除高位0
  while (n > 1 && str[n - 1] == '0') {
    str[n - 1] = '\0';
    n--;
  }

  // 第五步：翻转
  std::reverse(str, str + n);
  printf("%s\n", str);

  return 0;
}