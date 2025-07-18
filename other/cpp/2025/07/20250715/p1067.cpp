/*
ID: tiankonguse
TASK: p1067
LANG: C++
MAC EOF: ctrl+D
link: http://www.cqjjzx.com:83/problem.php?id=1067
PATH: 1067: 求数位与反序
submission:

题目：输入一个不多于四位的整数，输出它的位数，并在第二行输出它反序的数字。
输入：一个不多于四位的整数
输出：两行，第一行输出这个整数的位数，第二行输出它的反序数字。
*/
#define TASK "p1067"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void Solver() {  //
  int n;
  string buf;
  scanf("%d", &n);
  int signFlag = 1;
  if (n < 0) {
    signFlag = -1;
    n = -n;
  }
  if (n >= 10000) {
    buf = "五位数";
  } else if (n >= 1000) {
    buf = "四位数";
  } else if (n >= 100) {
    buf = "三位数";
  } else if (n >= 10) {
    buf = "二位数";
  } else if (n >= 1) {
    buf = "一位数";
  } else {
    buf = "一位数";
  }
  int rn = 0;
  while (n) {
    rn = rn * 10 + n % 10;
    n /= 10;
  }
  printf("%s\n%d\n", buf.c_str(), rn * signFlag);
}

int main(int argc, char** argv) {
  Solver();
  return 0;
}

/*

*/