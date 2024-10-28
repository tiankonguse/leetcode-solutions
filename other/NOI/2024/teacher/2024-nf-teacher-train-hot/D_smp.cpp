#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
char str[N];
int n;
bool IsNine() {
  for (int i = 0; i < n; i++) {
    if (str[i] != '9') {
      return false;
    }
  }
  return true;
}
bool ImageOk() {
  // 0 1 2 3
  //     |
  // 0 1 2 3 4
  //     |
  for (int r = (n + 1) / 2; r < n; r++) {
    if (str[r] == str[n - 1 - r]) continue;
    if (str[r] < str[n - 1 - r]) {
      return true;
    }
    if (str[r] > str[n - 1 - r]) {
      return false;
    }
  }
  return false;  // 自身是回文串，不满足
}

int main() {
  scanf("%s", str);
  n = strlen(str);

  if (IsNine()) {  //  999 => 1001
    memset(str, '0', sizeof(char) * (n + 1));
    str[0] = str[n] = '1';
    n++;
    str[n + 1] = '\0';
  } else if (n == 1) {  // 0~8
    str[0]++;
  } else {
    // 判断左半部不变，右半部相等时是否是更大的数字
    if (!ImageOk()) {
      // 0 1 2 3
      //   |
      // 0 1 2 3 4
      //     |
      for (int l = (n - 1) / 2; l >= 0; l--) {  // 左半部加1
        if (str[l] != '9') {
          str[l]++;
          break;
        }
        str[l] = '0';  // 进位
      }
    }

    // 右半部复制一份
    for (int l = 0, r = n - 1; l < r; l++, r--) {
      str[r] = str[l];
    }
  }

  printf("%s\n", str);

  return 0;
}