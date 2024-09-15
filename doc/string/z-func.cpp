// https://oi-wiki.org/string/z-func/

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
