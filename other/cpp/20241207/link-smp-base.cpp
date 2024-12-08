#include <bits/stdc++.h>
using namespace std;
struct SingleLink {
  int _value;
  SingleLink* _next;
  // SingleLink() {//初始化成员的值
  //	_next=NULL;
  // }
};

// 创建值为x的新结点,返回结点的位置
SingleLink* CreateNode(int x) {
  SingleLink* p = new SingleLink;  // 创建新结点p
  p->_value = x;
  p->_next = NULL;
  return p;
}
// 初始化链表
SingleLink* CreateSingleLink() {      // 返回头节点
  SingleLink* head = new SingleLink;  // 生成头结点
  head->_next = NULL;
  return head;
}
// 输出单向链表
void PrintSingleLink(SingleLink* head) {
  SingleLink* p = head->_next;  // 跳过头结点
  while (p != NULL) {           // 直到到达尾部结点
    printf("%d ", p->_value);
    p = p->_next;  // 指针往后移
  }
  printf("\n");  // 输出后换行
}

// 查找第i个结点
SingleLink* FindByPos(SingleLink* head, int i) {
  if (i == 0) return head;
  SingleLink* p = head->_next;  // 跳过头节点
  int index = 1;
  while (p != NULL) {
    if (index == i) {
      return p;  // 返回位置
    }
    index++;
    p = p->_next;
  }
  return NULL;
}
// 查找值x的位置
int FindByValue(SingleLink* head, int x) {
  SingleLink* p = head->_next;  // 跳过头节点
  int pos = 1;                  // 从第一个结点开始
  while (p != NULL) {
    if (p->_value == x) {
      return pos;  // 返回第几个结点
    }
    pos++;
    p = p->_next;
  }
  return -1;  // 代表没有找到
}
// 查找值为x的所有结点的位置，并返回找到的结点个数
// 用数组ret存储所有结点的位置
int FindAllValue(SingleLink* head, int x, int ret[]) {
  SingleLink* p = head->_next;  // 跳过头节点
  int pos = 1;                  // 第1个结点开始
  int index = 0;                // 统计结点的个数
  while (p != NULL) {
    if (p->_value == x) {
      ret[index++] = pos;
    }
    pos++;
    p = p->_next;
  }
  return index;  // 返回个数
}

// 修改第i个结点的值为t
void UpdataByPos(SingleLink* head, int i, int t) {
  SingleLink* p = FindByPos(head, i);  // 找到第i个结点的位置
  p->_value = t;                       // 修改值
}
// 修改值为x的结点为t（假设只有一个x)
void UpdataByValue(SingleLink* head, int x, int t) {
  int p = FindByValue(head, x);  // 找到值为x的结点是第几个结点。
  UpdataByPos(head, p, t);       // 修改值
}

// 修改所有值为x的结点为t
void UpdataAllValue(SingleLink* head, int x, int t) {
  int ret[100];  // 存储结点的位置
  int index =
      FindAllValue(head, x, ret);  // 找到所有为x的值结点的位置存放在ret数组里面
  for (int i = 0; i < index; i++) {
    UpdataByPos(head, ret[i], t);  // 修改所有x结点的值
  }
}

// 删除第i个结点
void DeleteByPos(SingleLink* head, int i) {
  SingleLink* q = FindByPos(head, i - 1);  // 找到第i-1个结点的位置
  SingleLink* p = q->_next;                // 第i个结点的位置
  q->_next = p->_next;
  delete p;  // 删除结点p
}
// 删除值为x的结点（只有一个结点）
void DeletByValue(SingleLink* head, int x) {
  int pos = FindByValue(head, x);  // 找到值为x的结点是第几个结点。
  SingleLink* pre = FindByPos(head, pos - 1);  // 找到该结点前一个结点的位置
  SingleLink* p = pre->_next;                  // 要被删除的结点
  pre->_next = p->_next;
  delete p;  // 删除结点p
}
// 删除所有值为x的结点
void DeletAllValue(SingleLink* head, int x) {
  int ret[100];  // 存储结点的位置
  int index =
      FindAllValue(head, x, ret);  // 找到所有为x的值结点的位置存放在ret数组里面
  for (int i = index - 1; i >= 0; i--) {  // 从后往前移动
    DeleteByPos(head, ret[i]);            // 修改所有x结点的值
  }
}

// 第i个结点前面插入值x的新结点s
void InsertPosBefore(SingleLink* head, int i, SingleLink* s) {
  SingleLink* p = FindByPos(head, i - 1);  // 找到第i-1个结点的位置
  s->_next = p->_next;                     // s指向第i个结点
  p->_next = s;                            // 第i-1个结点指向s
}
// 第i个结点后面插入值x的新结点s
void InsertPosAfter(SingleLink* head, int i, SingleLink* s) {
  SingleLink* p = FindByPos(head, i);  // 找到第i个结点的位置
  s->_next = p->_next;                 // s指向第i个结点
  p->_next = s;                        // 第i个结点指向s
}

int main() {
  int num;  // 输入的数字
  SingleLink* head = CreateSingleLink();
  SingleLink* tail = head;
  while (scanf("%d", &num) != EOF) {
    SingleLink* s = CreateNode(num);  // 创建一个新结点
    tail->_next = s;                  // 插入到后面
    tail = s;                         // 更新tail结点
  }
  PrintSingleLink(head);
  int i, x;
  // 查找第i个结点的值
  i = 5;
  SingleLink* p = FindByPos(head, i);
  printf("查询：第%d个结点的值为：%d\n", i, p->_value);

  // 查找值为x的结点在链表中的位置
  x = 3;
  int pos = FindByValue(head, x);
  printf("查询：%d是链表的第%d个结点\n", x, pos);

  int t = 100;
  // 修改第i个结点的值为t
  printf("修改第%d个结点的值为%d:", i, t);
  UpdataByPos(head, i, t);
  PrintSingleLink(head);

  // 把值为x的结点的值修改为t
  printf("修改值为%d的结点的值为%d:", x, t);
  UpdataByValue(head, x, t);
  PrintSingleLink(head);

  // 删除第i个结点
  printf("删除第%d个结点后的链表为：", i);
  DeleteByPos(head, i);
  PrintSingleLink(head);

  // 删除值为t的结点
  printf("删除值为%d的结点后的链表为：", t);
  DeletByValue(head, t);
  PrintSingleLink(head);

  // 第i个结点前面插入值x的新结点s
  printf("在第%d个结点前面插入%d后的链表为:", i, x);
  SingleLink* s = CreateNode(x);
  InsertPosBefore(head, i, s);
  PrintSingleLink(head);

  printf("在第%d个结点后面插入%d后的链表为:", i, x);
  SingleLink* s1 = CreateNode(x);
  InsertPosAfter(head, i, s1);
  PrintSingleLink(head);

  // 查找所有值为x的位置
  int ret[100], j;
  int index = FindAllValue(head, x, ret);
  for (j = 0; j < index; j++) {
    printf("%d在链表的第%d个位置\n", x, ret[j]);
  }
  // 修改所有值为x为t
  t = 300;
  printf("所有的%d值修改为%d后的链表:", x, t);
  UpdataAllValue(head, x, t);
  PrintSingleLink(head);

  // 删除所有值为t的结点
  printf("所有的%d值删除后的链表:", t);
  DeletAllValue(head, t);
  PrintSingleLink(head);
  return 0;
}
