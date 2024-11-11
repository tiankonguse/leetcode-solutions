#include <bits/stdc++.h>
using namespace std;
void rev(char s[])  // 将字符串s前后颠倒
{
  int len = strlen(s);
  for (int i = 0; i < len / 2; ++i) swap(s[i], s[len - 1 - i]);
}
int main() {
  char s[505], w[500][505];
  cin.getline(s, 505);
  int len = strlen(s), wi = 0, wj = 0;
  for (int i = 0; i <= len; ++i) {
    if (s[i] == ' ' || s[i] == '\0') {
      w[wi++][wj] = '\0';
      wj = 0;
    } else
      w[wi][wj++] = s[i];
  }
  for (int i = 0; i < wi; ++i) {
    rev(w[i]);
    printf("[%s]", w[i]);
    printf(" [%d]",i);
  }
  return 0;
}
