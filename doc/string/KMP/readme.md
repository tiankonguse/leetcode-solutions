# KMP  

## next 函数

next 函数用于记录模式串中每个位置之前的字符串的最长相等前后缀的长度。  
一般也称为前缀函数(Prefix function)。  


例如下面的样例，假设 `t[0...k-1]` 是模式串 `t` 的前缀，`t[j-k...j-1]` 是模式串 `t` 的后缀，且 `t[0...k-1] == t[j-k...j-1]`，那么 `next[j] = k`。  


```text
t[0] t[1] t[2] ... t[k-1] t[k] ... t[j-k] t[j-k+1] ... t[j-1] t[j]
```


可以发现，`next[j] = k` 的含义是 `t[0...k-1] == t[j-k...j-1]`。
k 指向前缀匹配串的下一个位置。  
j 也是指向后缀匹配串的下一个位置。  


下面是计算前缀函数的代码实现：  



```cpp
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
```




## 参考  


https://oi-wiki.org/string/kmp/

https://cp-algorithms.com/string/prefix-function.html

