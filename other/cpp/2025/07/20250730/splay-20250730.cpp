#include <bits/stdc++.h>
using namespace std;
struct SplayNode {
  int data;           // 结点的数值
  SplayNode *lchild;  // 结点的左孩子
  SplayNode *rchild;  // 结点的右孩子
  SplayNode *parent;  // 结点的父亲
  // 构造函数初始化
  SplayNode(int val) : data(val), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
};
// 中序打印
void inoderprint(SplayNode *root) {
  if (root == nullptr) return;
  inoderprint(root->lchild);
  printf("%d ", root->data);
  inoderprint(root->rchild);
}
// 将节点x向右旋转
void right_rotate(SplayNode *x) {
  SplayNode *y = x->parent;  // x的父亲
  SplayNode *z = y->parent;  // y的父亲

  assert(y->lchild == x);
  y->lchild = x->rchild;  // x原来的右孩子变为y的左孩子
  if (x->rchild != nullptr) {
    x->rchild->parent = y;  // 维护父亲：y成为x的右孩子的父亲
  }

  x->rchild = y;  // y成为x的右孩子
  y->parent = x;  // 维护父亲

  x->parent = z;           // x顶替y的位置，更新父亲
  if (z != nullptr) {      // 如果z这个节点存在
    if (z->lchild == y) {  // 如果y原来是z的左儿子，x就顶替它成为左儿子，否则是右儿子
      z->lchild = x;
    } else {
      z->rchild = x;
    }
  }
}
// 将节点x向左旋转
void left_rotate(SplayNode *x) {
  SplayNode *y = x->parent;  // x的父亲
  SplayNode *z = y->parent;  // y的父亲
  assert(y->rchild == x);
  y->rchild = x->lchild;  // x原来的左孩子变为y的右孩子
  if (x->lchild != nullptr) {
    x->lchild->parent = y;  // 维护父亲，y就成了x的左孩子的父亲
  }
  y->parent = x;  // 维护父亲，x成了y的父亲
  x->lchild = y;  // y成了x的左孩子

  x->parent = z;           // x顶替y的位置，x的父亲变为y的父亲
  if (z != nullptr) {      // 如果z存在
    if (z->lchild == y) {  // 如果y原来是z的左儿子，x就顶替它成为左儿子，否则是右儿子
      z->lchild = x;
    } else {
      z->rchild = x;
    }
  }
}
// 双层伸展算法,将x伸展到goal的孩子位置
void splay(SplayNode *x, SplayNode *goal = nullptr) {
  while (x->parent != goal) {  // 只要x没有旋转到目标节点
    SplayNode *y = x->parent;  // 获取当前状态x的父亲
    SplayNode *z = y->parent;  // 获取当前状态y的父亲
    // 第一种情况，x的父节点就是目标节点
    if (z == goal) {
      if (x == y->lchild) {  // 如果x是y的左孩子，就右旋
        right_rotate(x);
      } else {  // 否则左旋
        left_rotate(x);
      }
    }
    // 第二种情况，x和y都是父亲的左孩子或右孩子
    else if (x == y->lchild && y == z->lchild) {
      right_rotate(y);
      right_rotate(x);
    } else if (x == y->rchild && y == z->rchild) {
      left_rotate(y);
      left_rotate(x);
    }
    // 第三种情况，x是父亲的左孩子，y是父亲的右孩子
    else if (x == y->lchild && y == z->rchild) {
      right_rotate(x);
      left_rotate(x);
      // 第三种情况，y是父亲的左孩子，x是父亲的右孩子
    } else if (x == y->rchild && y == z->lchild) {
      left_rotate(x);
      right_rotate(x);
    }
  }
  // 特殊处理:如果目标节点是根节点，更新新的根节点
  if (goal == nullptr) {
    x->parent = nullptr;
  }
}
// 查找值为val的节点
SplayNode *findnode(SplayNode *p, int val) {  // 从根节点开始查找值为val的节点
  if (p == nullptr) {
    return nullptr;
  } else if (p->data == val) {
    splay(p, nullptr);  // 将找到的节点伸展到根
    return p;
  } else if (p->data > val) {  // 在左子树中查找
    return findnode(p->lchild, val);
  } else {  // 在右子树中查找
    return findnode(p->rchild, val);
  }
}
// 插入节点
SplayNode *insertnode(SplayNode *p, int val) {
  if (p == nullptr) {
    return new SplayNode(val);  // 生成新节点
  } else if (p->data == val) {  // 不插入
    splay(p, nullptr);
    return p;
  } else if (p->data > val) {  // 左子树中插入
    if (p->lchild == nullptr) {
      SplayNode *newNode = new SplayNode(val);
      p->lchild = newNode;
      newNode->parent = p;
      splay(newNode, nullptr);
      return newNode;
    } else {
      return insertnode(p->lchild, val);
    }
  } else {  // 右子树中插入
    if (p->rchild == nullptr) {
      SplayNode *newNode = new SplayNode(val);
      p->rchild = newNode;
      newNode->parent = p;
      splay(newNode, nullptr);
      return newNode;
    } else {
      return insertnode(p->rchild, val);
    }
  }
  //   splay(p, nullptr);  // 将插入的节点伸展到根
  //   return p;
}
// 查找左子树中的最大值
SplayNode *findmax(SplayNode *p) {
  while (p->rchild) {
    p = p->rchild;
  }
  splay(p, nullptr);  // 将最大值伸展到根节点
  return p;
}

// 查找右子树中的最小值
SplayNode *findmin(SplayNode *p) {
  while (p->lchild) {
    p = p->lchild;
  }
  splay(p, nullptr);  // 将最大值伸展到根节点
  return p;
}
// 求为val的节点的前驱
SplayNode *findpre(SplayNode *p, int val) {
  SplayNode *res = nullptr;
  if (p == nullptr) {
    return nullptr;
  } else if (p->data >= val) {  // 在左子树中查找
    return findpre(p->lchild, val);
  } else {  // 在右子树中查找
    SplayNode *temp = findpre(p->rchild, val);
    if (temp != nullptr) {
      res = temp;
    } else {
      res = p;
      splay(p, nullptr);  // 将最大值伸展到根节点
    }
  }
  return res;
}

// 求值为val的节点的后继
SplayNode *findnext(SplayNode *p, int val) {
  SplayNode *res = nullptr;
  if (p == nullptr) {
    return nullptr;
  } else if (p->data <= val) {  // 在右子树中查找
    return findnext(p->rchild, val);
  } else {
    res = p;
    SplayNode *temp = findnext(p->lchild, val);
    if (temp != nullptr) {
      res = temp;
    }
  }
  splay(res, nullptr);  // 将找到的后继节点伸展到根
  return res;
}
// 删除值为val的节点
SplayNode *deletenode(SplayNode *p, int val) {
  SplayNode *newroot = nullptr;  // 定义新根节点
  if (p == nullptr) {
    return nullptr;
  }
  printf("p root=%d\n", p->data);
  inoderprint(p);
  printf("\n");
  newroot = findnode(p, val);
  printf("root=%d\n", newroot->data);
  inoderprint(newroot);
  printf("\n");
  p = newroot;

  if (newroot != nullptr) {  // 找到值为val的节点
    // 实现分裂
    SplayNode *left = newroot->lchild;
    SplayNode *right = newroot->rchild;
    printf("pval=%d val=%d\n", newroot->data, val);
    assert(left == nullptr);
    assert(right != nullptr);
    if (left != nullptr) {
      left->parent = nullptr;
    }
    if (right != nullptr) {
      right->parent = nullptr;
    }
    // 合并
    if (left != nullptr) {      // 如果有左子树
      newroot = findmax(left);  // 找到左子树中的最大值并伸展到根节点
      newroot->rchild = right;  // 右子树直接变成新节点的右子树
      right->parent = newroot;  // 更新父节点
    } else {                    // 没有左子树，直接右子树为新的根
      newroot = right;
    }
    delete p;  // 删除值为val节点

    return newroot;  // 返回新节点
  }
  return newroot;  // 没找到，返回最新的根节点
}

int main() {
  SplayNode *root = nullptr;
  int a[] = {24, 15, 2, 9, 18, 30, 21};
  for (int i = 0; i < 7; i++) {
    root = insertnode(root, a[i]);
  }
  // 中序打印伸展树
  //   inoderprint(root);
  //   printf("\n");
  //   int b[] = {34, 10, 18, 2, 30, 11};
  //   for (int i = 0; i < 6; i++) {
  //     if (findnode(root, b[i])) {
  //       printf("%d存在\n", b[i]);
  //     } else {
  //       printf("%d不存在\n", b[i]);
  //     }
  //   }
  //   // 查找节点的前驱
  //   for (int i = 0; i < 7; i++) {
  //     SplayNode *preans = findpre(root, a[i]);
  //     if (preans == nullptr) {
  //       printf("%d没有前驱节点\n", a[i]);
  //     } else {
  //       printf("%d的前驱是%d\n", a[i], preans->data);
  //     }
  //   }
  //   // 查找节点的后继
  //   for (int i = 0; i < 7; i++) {
  //     SplayNode *nxtans = findnext(root, a[i]);
  //     if (nxtans == nullptr) {
  //       printf("%d没有后继节点\n", a[i]);
  //     } else {
  //       printf("%d的后继是%d\n", a[i], nxtans->data);
  //     }
  //   }
  inoderprint(root);
  printf("\n");
  // 删除值为val的节点
  int val = 2;
  root = deletenode(root, val);
  // 中序打印伸展树
  inoderprint(root);
  printf("\n");
  return 0;
}