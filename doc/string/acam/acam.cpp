
#include <bits/stdc++.h>

/*
AC 自动机模板

支持多个 AC 自动机同时工作。  
每个 AC 自动机有自己的 root 节点，通过 root 节点操作对应的 AC 自动机。

int root = AC::NextNode();  // 创建一个 AC 自动机，返回其 root 节点编号
AC::insert(root, pattern);  // 向对应 AC 自动机插入模式串
AC::build(root);            // 构建对应 AC 自动机
ll res = AC::query(root, text);  // 在对应 AC 自动机中查询 text 中出现的模式串总数

*/

namespace AC {
constexpr int kNodeSize = 1e7 + 6;
const int kKind = 27;
struct Node {
  int son[kKind];  // 子结点
  int cnt;         // 尾为该结点的串的个数
  int fail;        // fail 指针

  void init() {  // 结点初始化
    memset(son, 0, sizeof(son));
    cnt = fail = 0;
  }
} tr[kNodeSize];

int tot = 0;  // 结点总数

int NextNode() {
  int id = tot++;
  tr[id].init();
  return id;
}
int Hash(char c) {
  if (c == ' ') return kKind - 1;  // 特殊字符
  return c - 'a';
}

void insert(const int root, char s[]) {
  int u = root;
  for (int i = 0; s[i]; i++) {
    int& son = tr[u].son[Hash(s[i])];  // 下一个子结点的引用
    if (!son) son = NextNode();        // 如果没有则插入新结点，并初始化
    u = son;                           // 从下一个结点继续
  }
  tr[u].cnt++;
}

void build(const int root) {
  queue<int> q;
  // 为每个独立的 root 设置自己的 fail/缺失转移指向自己
  tr[root].fail = root;
  // 根节点的直接子结点：设置其 fail 为 root，并入队；根节点缺失转移指向 root 自身
  for (int i = 0; i < kKind; i++) {
    if (tr[root].son[i]) {
      tr[tr[root].son[i]].fail = root;
      q.push(tr[root].son[i]);
    } else {
      tr[root].son[i] = root;  // 根节点缺失转移指向 root 自身
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < kKind; i++) {
      if (tr[u].son[i]) {                               // 存在对应子结点
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  // 只用跳一次 fail 指针
        q.push(tr[u].son[i]);                           // 并加入队列
      } else {
        tr[u].son[i] = tr[tr[u].fail].son[i];  // 将不存在的字典树的状态链接到了失配指针的对应状态
      }
    }
  }
}

ll query(const int root, char t[]) {
  int u = root;
  ll res = 0;
  for (int i = 0; t[i]; i++) {
    u = tr[u].son[Hash(t[i])];  // 转移
    // 沿 fail 链累加，终止条件为回到当前 automaton 的 root
    for (int j = u; j != root; j = tr[j].fail) {
      res += tr[j].cnt;
    }
    // 如果 root 本身也为模式结尾（极少见），也需要计入
    if (tr[root].cnt) res += tr[root].cnt;
  }
  return res;
}
}  // namespace AC
