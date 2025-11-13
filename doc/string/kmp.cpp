
#include <bits/stdc++.h>


// 前缀函数 next[j]： 前缀 [0,j] 的最长公共前后缀的长度
// 即第 j 位匹配失败时，说明 pat[0,j-1] 与前缀是匹配的，此时 j 应该回退到 next[j-1]+1 重新开始匹配
// 扩展: 计算 Next 是一个在线算法，可以按顺序计算 Next 数组，故可以计算树上的 Next
//
// 应用:
// - 在字符串中查找子串：Knuth–Morris–Pratt 算法
// - 字符串的周期: n - (next[n-1]+1)
// - 统计每个前缀的出现次数
// - 一个字符串中本质不同子串的数目
// - 字符串压缩
// - 根据前缀函数构建一个自动机
// https://oi-wiki.org/string/kmp/
// 

vector<int> next;
void getNext(const char* pat) {
  for (int i = 1; pat[i]; ++i) {
    int k = next[i - 1];
    while (k >= 0 && pat[k + 1] != pat[i]) {
      k = next[k];
    }
    if (pat[k + 1] == pat[i]) {
      next[i] = k + 1;
    }
  }
}


int kmp(const char* str, const char* pat) {
  next.resize(strlen(pat) + 1, -1);
  getNext(pat);
  int i = 0, j = 0;
  while (str[i] && pat[j]) {
    if (pat[j] == str[i]) {
      ++i;
      if (!pat[++j]) {
        return i - j;
      }
    } else if (j == 0) {
      ++i;
    } else {
      j = next[j - 1] + 1;
    }
  }
  return -1;
}