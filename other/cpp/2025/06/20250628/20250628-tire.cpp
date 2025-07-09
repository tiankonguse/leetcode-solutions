#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
// 多孩子表示法
struct node {
  bool endflag;   // 该结点是否是一个串的结束
  int child[26];  // 孩子结点
  node() {        // 构造函数初始化成员变量
    endflag = false;
    memset(child, 0, sizeof(child));
  }
};
node trie[N];

int tot = 1;  // tot表示新分配的结点的位置
// 将字符串s插入字典树
void insert(string s) {
  int len = s.length();
  int p = 1;  // p表示当前结点的位置，从1开始
  for (int i = 0; i < len; i++) {
    int ch = s[i] - 'a';           // 计算当前字符的索引位置
    if (trie[p].child[ch] == 0) {  // 当前字符没有存储
      trie[p].child[ch] = ++tot;   // 把++toto位置分配给这个字符
    }
    p = trie[p].child[ch];  // 继续沿着下一个结点插入字符
  }
  trie[p].endflag = true;  // 标记单词结束
}
// 在字典树中查找字符串s,存在返回true，否则返回false
bool search(string s) {
  int len = s.length();
  int p = 1;  ////p表示当前结点的位置，从1开始
  for (int i = 0; i < len; i++) {
    int ch = s[i] - 'a';
    if (trie[p].child[ch] == 0) {  // 如果当前位置值为0
      return false;
    }
    p = trie[p].child[ch];  // 继续向后查找
  }
  // 当字符串遍历完后，看是否有结束标记
  if (trie[p].endflag) {  // 有结束标记
    return true;
  } else {
    return false;
  }
}
int main() {
  int n;  // 表示单词的个数
  string str[1000];
  cin >> n;
  for (int i = 0; i < n; i++) {  // 输入所有的字符串
    cin >> str[i];
    insert(str[i]);  // 插入字符串
  }
  string t;  // 要查找的字符串
  cin >> t;
  // 在字典树中查找字符串
  cout << ((search(t)) ? "存在" : "不存在") << endl;
  return 0;
}