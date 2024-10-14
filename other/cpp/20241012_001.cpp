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
  string a;
  getline(cin, a);

  // 输入: 1 1 + 3 *
  // 输出  6
  for (int i = 0; i < a.length(); i++) {
    if (isdigit(a[i])) {
      shu.push(a[i] - '0');
      continue;
    }
    if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/') {
      hou = shu.top();
      shu.pop();
      qian = shu.top();
      shu.pop();
      shu.push(suan(qian, hou, a[i]));
    }
    // 忽略括号
  }
  cout << shu.top();
  return 0;
}