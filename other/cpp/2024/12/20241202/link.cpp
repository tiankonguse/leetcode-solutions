#include <bits/stdc++.h>

int n;
int link_nxt[100];
int link_data[100];

void print_list() {
  for (int i = link_nxt[0]; i != -1; i = link_nxt[i]) {  // i表示第i个元素
    printf("%d ", link_data[i]);
  }
  printf("\n");
}
void creat_list() {
  scanf("%d", &n);  // 输入n个数字
  for (int i = 1; i <= n; i++) {
    scanf("%d", &link_data[i]);  // 输入当前结点的数据域
    link_nxt[i - 1] = i;          // 第i个结点的地址（位置）
    link_nxt[i] = -1;             // 最后一个结点的next指针
  }
}

int main() {
  creat_list();
  print_list();

  return 0;
}
