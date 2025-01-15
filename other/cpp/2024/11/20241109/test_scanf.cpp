/*
测试 scanf 的各种功能

*/
#include <bits/stdc++.h>

using namespace std;

/*
in: abcdefd
out: str1[abc] str2[defd]
*/
void testWidthString() {
  char str1[11], str2[11];
  scanf("%3s%s", str1, str2);
  printf("str1[%s] str2[%s]\n", str1, str2);
}

/*
in: 12345abcde
out: str1[12345] str2[abcde]
*/
void testMatchString() {
  char str1[11], str2[11];
  scanf("%[0-9]%s", str1, str2);
  printf("str1[%s] str2[%s]\n", str1, str2);
}

/*
in: abcde12345
out: str1[abcde] str2[12345]
*/
void testNoMatchString() {
  char str1[11], str2[11];
  scanf("%[^0-9]%s", str1, str2);
  printf("str1[%s] str2[%s]\n", str1, str2);
}

/*
in: a b c d e
out: str1[a b c d e]
*/
void testReadLine() {
  char str1[111];
  scanf("%[^\n]", str1);
  printf("str1[%s]\n", str1);
}

/*
in: 12345abcde
out: str1[abcde]
*/
void testSkipNum() {
  char str1[11];
  scanf("%*[0-9]%s", str1);
  printf("str1[%s]\n", str1);
}

/*
in: 123 c
out: a[123] b[c]
*/
void testSkipSpace() {
  int a;
  char b;
  scanf("%d %c", &a, &b);
  printf("a[%d] b[%c]\n", a, b);
}
void testSkipSpace2() {
  int a;
  char b;
  scanf("%d%*c%c", &a, &b);
  printf("a[%d] b[%c]\n", a, b);
}

/*
in: 123    4
out: a[123] b[4]
解释：scanf 中有 2 个空格，输入中有 5 个空格， %c 正常读取
结论：格式中有空格，可以跳过连续多个空格
*/
void testSkipMoreSpace() {
  int a;
  char b;
  scanf("%d  %c", &a, &b);
  printf("a[%d] b[%c]\n", a, b);
}

/*
in1: a 123 c as sda
in2: b 456 c as sda
out: a[a] str1[123] b[b] str2[456]
*/
void testSkipLine() {
  char a, b;
  char str1[11], str2[11];
  scanf("%c%s%*[^\n]%*c", &a, str1);
  scanf("%c%s%*[^\n]%*c", &b, str2);
  printf("a[%c] str1[%s] b[%c] str2[%s]\n", a, str1, b, str2);
}
/*
in: 123 sasasa
out: str[sasasa]
*/
void testNoFormat() {
  char str[11];
  scanf("123 %s", str);
  printf("str[%s]\n", str);
}

int main(int argc, char** argv) {
  testNoFormat();

  return 0;
}

/*

*/