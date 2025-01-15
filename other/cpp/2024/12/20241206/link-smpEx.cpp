
struct SingleLink {
  SingleLink(int value = 0) : _value(value), _next(NULL) {}
  int _value;
  struct SingleLink* _next;
};

SingleLink*& Next(SingleLink* node) { return node->_next; }
int& Data(SingleLink* node) { return node->_value; }

// 初始化链表
SingleLink* CreateSingleLink() {  // 返回头节点
  return new SingleLink(0);
}

SingleLink* CreateNode(int x) {  // [0,n] 已经分配，从 n+1 位置分配节点储存 x
  return new SingleLink(x);
}

void Release(SingleLink* node) {
  // do nothing
  delete node;
  node = nullptr;
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
  head = Next(head);  // 跳过头节点
  while (head != nullptr) {
    if (Data(head) == value) break;
    head = Next(head);
  }
  return head;
}

// 查找值的位置
int FindValuePos(SingleLink* head, int value) {
  head = head->_next;  // 跳过头节点
  int pos = 0;
  while (head != nullptr) {
    if (head->_value == value) {
      return pos;
    }
    head = head->_next;
    pos++;
  }
  return -1;
}
// 查找位置
SingleLink* FindByPos(SingleLink* head, int pos) {
  if (pos == -1) return head;  // 查找第一个的上一个，即头指针
  head = head->_next;          // 跳过头节点
  int index = 0;
  while (head != nullptr) {
    if (index == pos) {
      return head;
    }
    index++;
    head = head->_next;
  }
  return nullptr;  // 越界
}

void DeleteByValue(SingleLink* head, int value) {
  int pos = FindValuePos(head, value);
  if (pos == -1) return;  // 不存在
  SingleLink* pre = FindByPos(head, pos - 1);
  SingleLink* now = pre->_next;
  pre->_next = now->_next;
  Release(now);
}
