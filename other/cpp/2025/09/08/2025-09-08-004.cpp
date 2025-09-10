// 前缀表达式求值（只有一位数字）

#include <bits/stdc++.h>
using namespace std;
// 进行运算操作
int solve(int x, int y, char op) {
  switch (op) {
    case '+':
      return y + x;  // 注意这里两个数字的顺序
    case '-':
      return y - x;
    case '*':
      return y * x;
    case '/':
      return y / x;
  }
}
int main() {
  char str[100];  // 存储表达式
  stack<int> st;  // 栈
  cin.getline(str, 100);
  int num;  // 存储每个数字
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    printf("i=%d [%c]\n", i, str[i]);
  }

  for (int i = len - 1; i >= 0; i--) {                                              // 从右往左读
    if (str[i] >= '0' && str[i] <= '9') {                                           // 如果是数字，直接入栈
      num = str[i] - '0';                                                           // 转化为数字
      st.push(num);                                                                 // 入栈
    } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {  // 如果是运算符，依次出战两个数字
      int x = st.top();                                                             // 取栈顶数字
      st.pop();
      int y = st.top();  // 取第二个栈顶数字
      st.pop();
      // 进行运算
      int ans = solve(x, y, str[i]);
      st.push(ans);  // 入栈
    }
  }
  cout << st.top() << endl;  // 最终栈顶元素就是答案
  return 0;
}
/*
* 5 * + 3 8 4


220

*/
