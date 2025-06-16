#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000;
vector<int> nextt(maxn);

// 暴力枚举法计算Next数组
void get_next(string t) {
  int m = t.length();
  // next[0] 固定为 -1
  nextt[0] = -1;
  // 计算 next[1] 到 next[m-1]
  for (int i = 1; i < m; i++) {  // 考察子串 t[0...i-1] 的最长公共前后缀
    nextt[i] = 0;                // 设置初始值
    // 从最长可能长度开始尝试
    for (int len = i - 1; len >= 1; len--) {
      bool match = true;  // 设置初始值
      // 检查前缀 t[0...len-1] 是否等于后缀 t[i-len...i-1]
      for (int j = 0; j < len; j++) {
        if (t[j] != t[i - len + j]) {
          match = false;
          break;
        }
      }
      // 如果找到匹配，设置next[i]并跳出循环
      if (match) {
        nextt[i] = len;
        break;
      }
    }
  }
}

int KMP0(string s, string t) {  // KMP算法
  int i = 0, j = 0;
  int slen = s.length();
  int tlen = t.length();
  get_next(t);  // 构建next数组
  while (i < slen && j < tlen) {
    if (j == -1 || s[i] == t[j]) {  // 如果相等，继续向后比较,注意防止后退到边界问题
      i++;
      j++;
    } else {  // 如果不相等，只需要j回退到next[j]
      j = nextt[j];
    }
    printf("i=%d j=%d\n", i, j);
  }
  if (j >= tlen) {
    return i - tlen;
  } else {
    return -1;
  }
}
// int KMP(string s, string t) {  // KMP算法
//   int i = 0, j = 0;
//   int slen = s.length();
//   int tlen = t.length();
//   get_next(t);  // 构建next数组
//   while (i < slen && j < tlen) {
//     if (s[i] == t[j]) {  // 如果相等，继续向后比较,注意防止后退到边界问题
//       i++;
//       j++;
//     } else if (j == 0) {
//       i++;    // 第一个就不相等，s 后移
//     } else {  // 如果不相等，只需要j回退到next[j]
//       j = nextt[j];
//     }
//     printf("i=%d j=%d\n", i, j);
//   }
//   if (j == tlen) {
//     return i - tlen;
//   } else {
//     return -1;
//   }
// }
int main() {
  string s = "abaabaabeca";
  string t = "abaabe";
  cout << KMP0(s, t) << endl;
//   cout << KMP(s, t) << endl;
  return 0;
}


/*

第一次匹配到最后一个为止，不相等。  

abaabaabeca
abaabe


匹配的串标记起来，方便区分。  

[abaab]aabeca
[abaab]e


右移1次：不匹配
[abaab]aabeca
 [abaab]e

右移2次：不匹配
[abaab]aabeca
  [abaab]e


右移3次：匹配
[abaab]aabeca
   [abaab]e


[abaab] 已经遍历过了，且与原串相等，正常需要不断右移，判断是否匹配。
人眼看的话，显然右移到 ab 可以匹配， ab 称为【真】最长公共前后缀，且可以预处理出来的。  



*/