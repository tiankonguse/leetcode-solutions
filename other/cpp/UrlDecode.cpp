#include <bits/stdc++.h>
using namespace std;

inline unsigned char FromHex(unsigned char x) {
  unsigned char y = 0;
  if (x >= 'A' && x <= 'Z')
    y = x - 'A' + 10;
  else if (x >= 'a' && x <= 'z')
    y = x - 'a' + 10;
  else if (x >= '0' && x <= '9')
    y = x - '0';
  return y;
}

inline std::string UrlDecode(const std::string &str) {
  std::string strTemp = "";
  size_t length = str.length();
  try {
    for (size_t i = 0; i < length; i++) {
      if (str[i] == '+')
        strTemp += ' ';
      else if (str[i] == '%') {
        assert(i + 2 < length);
        unsigned char high = FromHex((unsigned char)str[++i]);
        unsigned char low = FromHex((unsigned char)str[++i]);
        strTemp += high * 16 + low;
      } else
        strTemp += str[i];
    }
  } catch (...) {
  }
  return strTemp;
}

// ac
int main() {
  cout << UrlDecode("%24%3BUC1dVwGQ0N%7Ea%5E") << endl;
  return 0;
}
