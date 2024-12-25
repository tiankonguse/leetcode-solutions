F. Periodic Substring  F. 周期子串
time limit per test3 seconds
每次测试的时间限制3秒
memory limit per test512 megabytes
每个测试的内存限制512兆字节
Given the string 𝑠 . Find a maximum integer 𝑘  such that there is a non-empty substring in the string 𝑠  that is a concatenation of 𝑘  equal strings.
给定字符串 𝑠  。找到最大整数 𝑘  使得字符串中有一个非空子串 𝑠  这是一个串联 𝑘  相等的字符串。

Input  输入
The first line of input contains the string 𝑠  (1≤|𝑠|≤400000 ). The string consists of lowercase English letters.
输入的第一行包含字符串 s （ 1≤|s|≤400000 ）。该字符串由小写英文字母组成。

Output  输出
Print the desired value 𝑘 .
打印所需的值 k 。

Examples  例子
Input  输入Copy  复制
aabaaabaaabaaabaab
Output  输出Copy  复制
4
Input  输入Copy  复制
aabaabb
Output  输出Copy  复制
2
Input  输入Copy  复制
aaaa
Output  输出Copy  复制
4
Input  输入Copy  复制
ppppplppp
Output  输出Copy  复制
5
Input  输入Copy  复制
nn
Output  输出Copy  复制
2
Note  笔记
In the first example, a substring that repeats 4
 times is "abaa".
在第一个示例中，重复的子字符串 4 次是“ abaa ”。