#include <algorithm>  // 引入algorithm库用于使用max函数
#include <iostream>
#include <string>  // 引入string库用于string操作
using namespace std;

int main() {
  string s1, s4;
  string s2 = "", s3 = "";

  // 从输入读取二进制数
  cin >> s1;

  // 保存原始输入
  s4 = s1;

  // 将s1左移4位（相当于乘以16）
  // 这相当于给s1的末尾添加4个0
  s1 = s1 + "0000";

  // 由于在进行二进制加法时长度必须相同，这里向s2前添加4个0以匹配s1长度
  s2 = "0000" + s4;

  // 确保s1和s2的长度相同，为二进制加法运算做准备
  int max_length = max(s1.length(), s2.length());
  s1 = string(max_length - s1.length(), '0') + s1;
  s2 = string(max_length - s2.length(), '0') + s2;
  s3 = string(max_length, '0');  // 初始化结果字符串s3为0

  char carry = '0';  // 初始化进位变量为'0'
  for (int i = max_length - 1; i >= 0; i--) {
    // 对每一位执行二进制加法，包括进位
    int sum = (s1[i] - '0') + (s2[i] - '0') + (carry - '0');
    s3[i] = (sum % 2) + '0';  // 计算当前位置的结果
    carry = (sum / 2) + '0';  // 计算新的进位
  }

  // 如果最后还有进位，将其添加到最前面
  if (carry == '1') {
    s3 = "1" + s3;
  }

  // 如果字符串以0开始（除非整个字符串都是0），我们移除这些0
  size_t start_pos = s3.find_first_not_of("0");
  if (start_pos != string::npos) {
    s3 = s3.substr(start_pos);  // 去除前导0
  } else {
    s3 = "0";  // 如果字符串全是0，输出0
  }

  // 最终输出结果字符串s3
  cout << s3 << endl;

  return 0;  // 程序结束
}