/*
逆波兰式

*/
#include <bits/stdc++.h>
using namespace std;
double suan(double x, double y, char z) {
  if (z == '+') return x + y;
  if (z == '-') return x - y;
  if (z == '*') return x * y;
  if (z == '/') return x / y;
  return 0;
}
int main() {
  stack<double> shu;
  double qian, hou;
  stack<char> yun;  // 运算符
  string a;
  getline(cin, a);
  for (int i = 0; i < a.length(); i++) {
    if (isdigit(a[i])) {
      shu.push(a[i] - '0');
    }
    if (a[i] == '(') {
      yun.push(a[i]);
    }
    if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/') {
      // case1:  第一个运算符
      // case2:  当前乘法和除法，前一个是加或减法
      // case3:  前面是括号，还没遇到运算符
      if (yun.empty() || abs(a[i] - 44) != 1 && abs(yun.top() - 44) == 1 ||
          yun.top() == '(') {
        yun.push(a[i]);  //
        continue;
      }
      // 遇到 + 或者 1， 之前的可以运算了
      while (!yun.empty() && yun.top() != '(' &&
             !(abs(a[i] - 44) != 1 && abs(yun.top() - 44) == 1)) {
        hou = shu.top();
        shu.pop();
        qian = shu.top();
        shu.pop();
        shu.push(suan(qian, hou, yun.top()));
        yun.pop();
      }
      yun.push(a[i]);
    }
    if (a[i] == ')') {
      while (yun.top() != '(') {
        hou = shu.top();
        shu.pop();
        qian = shu.top();
        shu.pop();
        shu.push(suan(qian, hou, yun.top()));
        yun.pop();
      }
      yun.pop();
      continue;
    }
  }
  while (!yun.empty()) {
    hou = shu.top();
    shu.pop();
    qian = shu.top();
    shu.pop();
    shu.push(suan(qian, hou, yun.top()));
    yun.pop();
  }
  cout << shu.top();
  return 0;
}