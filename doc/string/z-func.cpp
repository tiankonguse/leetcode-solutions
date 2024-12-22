// https://oi-wiki.org/string/z-func/
// https://codeforces.com/edu/course/2/lesson/3
// https://cp-algorithms.com/string/z-function.html

/*
给一个下标以 0 为起点、长度为 n 的字符串 s。
函数 z[i] 表示 s 和 s[i,n-1]的最长公共前缀（LCP）的长度
特别地，z[0] = 0。

Z Algorithm 也称为扩展 KMP

下面若干样例展示了对于不同字符串的 Z 函数：

z(aaaaa) = [0, 4, 3, 2, 1]
z(aaabaab) = [0, 2, 1, 0, 2, 1, 0]
z(abacaba) = [0, 0, 1, 0, 3, 0, 1]

应用: 

-） 暴力计算 LCP ，O(n^2) 
https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/A

-) 不同时是前缀和后缀的子串个数

https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/B

-) 通配符，问所有匹配
构造 T + $ + S 和 RT + $ + RS,  找到所有的 TS[l] + 1 + RTS[r] >= tn 位置
https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/C

-) S 不包含 T 的子串个数
构造 T + $ + S， 如果 TS[i] == tn，则大于 tn 的后缀都包含 T，否则都不包含 T
注意：小于 tn 的子串都不包含 T
https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/D





- 匹配所有子串: 文本 t 中模式 p 中出现的次数
  1) 构造 s = p + '$' + t
  2) 计算 s 的 Z 函数
  3) count(Z[i] == |t|)
- 本质不同子串数


*/

// O(n) EXKMP 计算
std::vector<int> z_function(std::string s) {
  int n = s.length();
  std::vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
        ++z[i];
      }
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

void z_function(char* s, int n, int* z) {  //
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < n; i++) {
    z[i] = 0;
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
}

// O(n^2) 暴力计算
std::vector<int> z_function_trivial(std::string s) {
  int n = s.length();
  std::vector<int> z(n);
  for (int i = 1; i < n; ++i)
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
  return z;
}
