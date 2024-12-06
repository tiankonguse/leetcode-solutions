
struct SingleLink {
  SingleLink(int value = 0) : _value(value), _next(NULL) {}
  int _value;
  struct SingleLink* _next;
};

// 初始化链表
SingleLink* CreateSingleLink() {  // 返回头节点
  return new SingleLink(0);
}

SingleLink* CreateNode(int x) {  // [0,n] 已经分配，从 n+1 位置分配节点储存 x
  return new SingleLink(x);
}

// 插入节点
void InsertAfter(SingleLink* head, SingleLink* node) {
  node->_next = head->_next;
  head->_next = node;
}

// 删除节点
void DeleteAfter(SingleLink* head) {
  if (head->_next) {
    SingleLink* node = head->_next;
    head->_next = node->_next;
    delete node;
  }
}

// 查找值
SingleLink* FindByValue(SingleLink* head, int value) {
  head = head->_next;  // 跳过头节点
  while (head != NULL) {
    if (head->_value == value) break;
    head = head->_next;
  }
  return head;
}

// 查找位置
SingleLink* FindByPos(SingleLink* head, int pos) {
  head = head->_next;  // 跳过头节点
  int index = 0;
  while (head != NULL) {
    if (index == pos) {
      return head;
    }
    index++;
    head = head->_next;
  }
  return NULL;  // 越界
}
