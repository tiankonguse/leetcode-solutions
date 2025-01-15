#include <bits/stdc++.h>

using namespace std;

int main() {
  string s1, s2;
  int n1, n2;
  
  int pre = 0;             // 进位
  string s(n1 + n2, '0');  // 最高是 n1+n2位，储存的逆序结果

  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < n1; j++) {
      const int a = s2[i] - '0';
      const int b = s1[j] - '0';
      const int now = s[i + j] - '0';  // 之前相乘时，当前位置的值
      int sum = now + a * b + pre;
      s[i + j] = '0' + (sum % 10);
      pre = sum / 10;
    }
  }
  if (pre) {  // 双层循环 n2-1 与 n1-1 可能进位，s1 和 s2
              // 没有前导零，所以最高位的进位需单独处理
    s[n1 + n2 - 1] = '0' + pre;
  }
}
