// http://noi.openjudge.cn/ch0107/19/
// 1）dst 数组开小了
// 2) 
#include <bits/stdc++.h>
using namespace std;
const int N = 66;
char s[N], t[N];
char s_new[2 * N];  // 构造新字符串
int main() {
  scanf("%s%s", s, t);
  int n, m;
  n = strlen(s);
  m = strlen(t);
  if (n < m) swap(s, t);
  strcpy(s_new, strcat(s, s));
  // cout<<s_new<<endl;
  if (strstr(s_new, t))
    printf("true\n");
  else
    printf("false\n");
  return 0;
}

char* strcat(char* dst, char* src) {
  char* p = dst;
  while (*p) p++;
  while (*src) {
    *p = *src;
    p++;
    src++;
  }
  *p = '\0';
  return dst;
}