#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000;
int cnt, ans, flag;  // 是不是第一个位置的标记
vector<int> nextt(maxn);
void tolow(string &s) {  // 注意，这样要用引用才能实现全部转化为小写字母
  int m = s.length();
  for (int i = 0; i < m; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] += 32;
    }
  }
}
// 递推计算Next数组
void get_next(string t) {
  int m = t.length();
  nextt[0] = -1;  // 初始条件
  int k = -1;
  int j = 0;
  // 计算 next[1] 到 next[m-1]
  while (j < m) {                   // 状态转移方程
    if (k == -1 || t[j] == t[k]) {  // 当匹配时
      nextt[++j] = ++k;
    }
    // 当不匹配时，根据next数组回退k的位置
    else {
      k = nextt[k];
    }
  }
}

int KMP(string s, string t, int pos) {  // KMP算法
  int i = pos, j = 0;
  cnt = 0;
  ans = -1;
  flag = 0;
  int slen = s.length();
  int tlen = t.length();
  get_next(t);  // 构建next数组
  while (i < slen) {
    if (j == -1 || s[i] == t[j]) {  // 如果相等，继续向后比较
      i++;
      j++;
    } else {  // 如果不相等，只需要j回退到next[j]
      j = nextt[j];
    }
    if (j >= tlen) {  // 完全匹配
      return i - tlen;
    }
  }
  return -1;
}

int main() {
  string s, t;
  getline(cin, s);  // 以行输入
  getline(cin, t);
  int slen = s.length();
  int tlen = t.length();
  s = ' ' + s + ' ';  // 首尾补空格
  t = ' ' + t + ' ';  // 首尾补空格
  tolow(s);           // 转化成小写
  tolow(t);
  cout << s << endl << t << endl;
  int firstpos = KMP(s, t, 0);
  if (firstpos == -1) {
    cout << "-1" << endl;
    return 0;
  } else {
    int cnt = 1;
    int t1 = firstpos + tlen - 1;
    while (t1 < slen) {
      t1 = KMP(s, t, t1);
      if (t1 != -1) {
        cnt++;
      }
      t1 = t1 + tlen - 1;
    }
    cout << cnt << " " << firstpos << endl;
  }

  return 0;
}
/*
To
to be or not to be is a question
*/