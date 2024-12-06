#include <bits/stdc++.h>

int linkData[100];
int linkNext[100];
int n = 1;
int head = 0;

int CreateList() {
  n = 1;
  head = 0;
  linkNext[head] = -1;
  return head;
}

int CreateNode(int x) {  // [0,n] 已经分配，从 n+1 位置分配节点储存 x
  ++n;
  linkData[n] = x;
  linkNext[n] = -1;
  return n;
}

void Release(int node) {
  // do nothing
}

// 插入节点
void InsertAfter(int head, int node) {
  linkNext[node] = linkNext[head];
  linkNext[head] = node;
}

// 删除节点
void DeleteAfter(int head) {
  if (linkNext[head] != -1) {
    int node = linkNext[head];
    linkNext[head] = linkNext[node];
    Release(node);
  }
}

// 查找值
int FindByValue(int head, int value) {
  head = linkNext[head];  // 跳过头节点
  while (head != -1) {
    if (linkData[head] == value) break;
    head = linkNext[head];
  }
  return head;
}

// 查找位置
int FindByPos(int head, int pos) {
  head = linkNext[head];  // 跳过头节点
  int index = 0;
  while (head != -1) {
    if (index == pos) break;
    index++;
    head = linkNext[head];
  }
  return head;
}

void PrintfList(int head) {
  head = linkNext[head];  // 跳过头节点
  printf("list: ");
  while (head != -1) {
    printf("->  %d ", linkData[head]);
    head = linkNext[head];
  }
  printf("\n");
}

int main() {
  int n;
  scanf("%d", &n);
  const int head = CreateList();
  int tail = head;
  for (int i = 0; i < n; i++) {
    // scanf("%d", &v);
    int node = CreateNode(i * 2);
    InsertAfter(tail, node);
    tail = node;
  }
  PrintfList(head);

  int head3 = FindByValue(head, 3);
  printf("v=3 data=%d\n", linkData[head3]);

  int head4 = FindByPos(head, 4);
  printf("pos=4 data=%d\n", linkData[head4]);

  return 0;
}
