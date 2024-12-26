#include <bits/stdc++.h>
using namespace std;

int judge(int *a, int *b, int len2) {    // 判断a是否能减b
  if (a[len2] > 0) return true;          // 如果 a 比 b 长, 一定可以除
  for (int i = len2 - 1; i >= 0; i--) {  // 从 a 的最高位开始比
    if (a[i] > b[i])
      return true;  // 除去相等位的最高位大于b,说明a比b大,可以除
    else if (a[i] < b[i])
      return false;  // 除去相等位的最高位小于b,说明a比b小，不可以除
  }
  return true;  // 如果a和b完全一样,可以除
}
int main() {
  char s1[1000];                     // 第一个大数据
  char s2[1000];                     // 第一个大数据
  int a[1000];                       // 存放被除数
  int b[1000];                       // 存放除数
  int s[1000];                       // 存放商
  memset(s, 0, sizeof(int) * 1000);  // 初始化都为0
  scanf("%s", s1);
  scanf("%s", s2);
  // 将高精度数据反序并存储在int数组里
  int len1 = strlen(s1);
  for (int i = 0; i < len1; i++) a[i] = s1[len1 - 1 - i] - '0';
  int len2 = strlen(s2);
  for (int i = 0; i < len2; i++) b[i] = s2[len2 - 1 - i] - '0';
  printf("a: ");
  for (int i = 0; i < len1; i++) printf("%d", a[i]);
  printf("\n");
  printf("b: ");
  for (int i = 0; i < len2; i++) printf("%d", b[i]);
  printf("\n");
  // 模拟两个数除法运算的过程。

  // 1000 / 33
  for (int i = len1 - len2; i >= 0; i--) {
    while (judge(a + i, b,
                 len2)) {  // 当前a能够减b时，一直减下去，直到不能减
      getchar();
      printf("i=%d s[i]=%d\n", i, s[i]);
      printf("a: ");
      for (int k = 0; k < len1; k++) printf("%d", a[k]);
      printf("\n");
      printf("b: ");
      for (int k = 0; k < len2; k++) printf("%d", b[k]);
      printf("\n");
      printf("s: ");
      for (int k = 0; k < len1; k++) printf("%d", s[k]);
      printf("\n");

      s[i]++;  // 总共减的次数是对应位置结果
      for (int j = 0; j < len2; j++) {
        if (a[i + j] >= b[j]) {
          a[i + j] -= b[j];
        } else {
          a[i + j + 1]--;  // 借1
          a[i + j] = a[i + j] + 10 - b[j];
        }
      }
    }
  }
  // 消除商的末尾0
  int len = len1;
  while (s[len1] == 0 && len1 > 0) {  // 从最后一个开始，但是要保留一位
    len1--;
  }
  // 消除余数的末尾0
  while (a[len] == 0 && len > 0) {  // 从最后一个开始，但是要保留一位
    len--;
  }
  // 倒序输出商和余数
  printf("s: ");
  for (int i = len1; i >= 0; i--) printf("%d", s[i]);
  printf("\n");
  printf("a: ");
  for (int i = len; i >= 0; i--) printf("%d", a[i]);
  printf("\n");

  return 0;
}

/*
426 12
*/