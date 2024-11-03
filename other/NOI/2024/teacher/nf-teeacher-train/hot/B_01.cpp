#include <cstring>
#include <iostream>
using namespace std;
int main() {
  string s1, s2, s3, s4;
  char b = '0', c;
  int n;
  cin >> s1;
  s4 = s1;
  s1 = '0' + s1 + "0000";
  s2 = "00000" + s4;
  s3.resize(s1.size(), '0');
  //   cout << s1 << endl;
  //   cout << s2 << endl;
  n = s1.length();
  int i = n - 1;
  while (i >= 0) {
    c = s1[i] ^ s2[i] ^ b;

    s3[i] = char(c);
    if ((s1[i] == '1' && s2[i] == '1') || (s1[i] == '1' && b == '1') ||
        (b == '1' && s2[i] == '1'))
      b = '1';
    else
      b = '0';
    // cout << char(c) << " " << b << endl;
    i--;
  }
  if (s3[0] == '1') cout << s3[0];
  for (int i = 1; i <= n - 1; i++) cout << s3[i];

  cout << endl;

  return 0;
}