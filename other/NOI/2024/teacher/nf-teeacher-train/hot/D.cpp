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
  memset(str, '0', sizeof(char) * (n + 1));

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

void DoImage() {
  for (int l = 0, r = n - 1; l < r; l++, r--) {
    str[r] = str[l];
  }
}

int main() {
  scanf("%s", str);
  n = strlen(str);

  if (IsNine()) {  //  999
    // printf("hit 999\n");
    memset(str, '0', sizeof(char) * (n + 1));
    str[0] = str[n] = '1';
    n++;
    str[n + 1] = '\0';
  } else if (n == 1) {  // 0~8
    // printf("hit 0-8\n");
    str[0]++;
  } else if (!ImageOk()) {
    // printf("hit image not ok\n");
    // 0 1 2 3   N=4
    //   |       P=1
    // 0 1 2 3 4 N=5
    //     |     P=2
    //   abcd[x<9]9999 | 8
    //=> abcd[x+1]0000 | 000[x+1]dcba
    for (int l = (n - 1) / 2; l >= 0; l--) {
      if (str[l] != '9') {
        str[l]++;
        break;
      }
      str[l] = '0';  // 进位
    }
    DoImage();  // 左半部加 1 之后，右半部复制左半部
  } else {
    DoImage();  // 右半部复制左半部，即可得到答案
  }

  printf("%s\n", str);

  return 0;
}