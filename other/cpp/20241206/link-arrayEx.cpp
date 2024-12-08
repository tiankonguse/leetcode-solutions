#include <bits/stdc++.h>

int linkData[100];
int linkNext[100];
int n = 1;
int head = 0;

int& Next(int node) { return linkNext[node]; }
int& Data(int node) { return linkData[node]; }

int CreateList() {
  n = 1;
  head = 0;
  Next(head) = -1;
  return head;
}

int CreateNode(int x) {  // [0,n] 已经分配，从 n+1 位置分配节点储存 x
  ++n;
  Data(n) = x;
  Next(n) = -1;
  return n;
}

void Release(int node) {
  // do nothing
}

// 插入节点
void InsertAfter(int head, int node) {
  Next(node) = Next(head);
  Next(head) = node;
}

// 删除节点
void DeleteAfter(int head) {
  if (Next(head) != -1) {
    int node = Next(head);
    Next(head) = Next(node);
    Release(node);
  }
}

// 查找值
int FindByValue(int head, int value) {
  head = Next(head);  // 跳过头节点
  while (head != -1) {
    if (Data(head) == value) break;
    head = Next(head);
  }
  return head;
}

// 查找值的位置
int FindValuePos(int head, int value) {
  head = linkNext[head];  // 跳过头节点
  int pos = 0;
  while (head != -1) {
    if (linkData[head] == value) {
      return pos;
    }
    head = linkNext[head];
    pos++;
  }
  return -1;
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
