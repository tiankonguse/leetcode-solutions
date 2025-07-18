#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int num, numTmp, reversed = 0;
  cin >> num;

  // 计算位数
  int count = 0;
  numTmp = num;
  while (numTmp != 0) {
    count++;
    numTmp /= 10;
  }

  // 反转数字
  numTmp = abs(num);
  while (numTmp != 0) {
    int digit = numTmp % 10;
    reversed = reversed * 10 + digit;
    numTmp /= 10;
  }

  if (num < 0) {
    reversed = -reversed;
  }

  // 判断count是几位数字
  string countStr;
  if (count == 1) {
    countStr = "一位数";
  }
  if (count == 2) {
    countStr = "二位数";
  }
  if (count == 3) {
    countStr = "三位数";
  }
  if (count == 4) {
    countStr = "四位数";
  }
  cout << countStr << endl;
  cout << reversed << endl;

  return 0;
}
/**************************************************************
    Problem: 1067
    User: 10000
    Language: C++
    Result: 正确
    Time:4 ms
    Memory:2084 kb
****************************************************************/