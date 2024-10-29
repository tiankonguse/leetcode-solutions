#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string s1, s4;
  string s2 = "", s3 = "";
  cin >> s1;

  // 17倍就是原数左移4位然后加上原数
  s4 = s1;           // Save original string
  s1 = s1 + "0000";  // Left shift s1 by 4 (Multiply by 16)
  s2 = "0000" + s4;  // Add 4 leading zeros for alignment

  // 对齐s1和s2的长度
  int max_length = max(s1.length(), s2.length());
  s1 = string(max_length - s1.length(), '0') + s1;
  s2 = string(max_length - s2.length(), '0') + s2;
  s3 = string(max_length, '0');

  char carry = '0';
  for (int i = max_length - 1; i >= 0; i--) {
    int sum = (s1[i] - '0') + (s2[i] - '0') + (carry - '0');
    s3[i] = (sum % 2) + '0';  // Current digit result
    carry = (sum / 2) + '0';  // Calculate new carry
  }

  if (carry == '1') {
    s3 = "1" + s3;  // Add carry if it's 1
  }

  // 输出删除前导0，除非全部都是0
  size_t start_pos = s3.find_first_not_of("0");
  if (start_pos != string::npos) {
    s3 = s3.substr(start_pos);
  } else {
    s3 = "0";  // All zeros edge case
  }

  cout << s3 << endl;  // 输出结果

  return 0;
}