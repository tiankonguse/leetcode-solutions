#include <bits/stdc++.h>
using namespace std;
void match(char str[], int len) {
  char a[260];   // 用数组模拟顺序栈
  int top = -1;  // 初始化栈
  for (int i = 0; i < len; i++) {
    if ((str[i] == '(') || (str[i] == '[') || (str[i] == '{')) {  // 左括号入栈
      top++;
      a[top] = str[i];
    } else if ((str[i] == ')') && (top != -1)) {
      if (a[top] == '(') {
        top--;  // 当前字符出栈
      } else
        break;
    } else if ((str[i] == ']') && (top != -1)) {
      if (a[top] == '[') {
        top--;  // 当前字符出栈
      } else
        break;
    } else if ((str[i] == '}') && (top != -1)) {
      if (a[top] == '{') {
        top--;  // 当前字符出栈
      } else
        break;
    }
  }
  if (top == -1) {
    printf("OK\n");
  } else
    printf("Wrong\n");
}

int main() {
  char str[260];
  cin.getline(str, 260);  // 以行输入
  int len = strlen(str);
  match(str, len);
  return 0;
}