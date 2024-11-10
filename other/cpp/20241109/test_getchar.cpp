/*
测试 scanf 的各种功能

*/
#include <bits/stdc++.h>

using namespace std;

char str[100][100];
int main(int argc, char** argv) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0;; j++) {
      char c = getchar();
      if (c == '\n') {
        str[i][j] = '\0';
        break;
      } else {
        str[i][j] = c;
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    printf("%s\n", str[i]);
  }

  return 0;
}

/*

*/