# 面试题 17.15. 最长单词

给定一组单词words，编写一个程序，找出其中的最长单词，且该单词由这组单词中的其他单词组合而成。若有多个长度相同的结果，返回其中字典序最小的一项，若没有符合要求的单词则返回空字符串。

示例：

输入： ["cat","banana","dog","nana","walk","walker","dogwalker"]
输出： "dogwalker"
解释： "dogwalker"可由"dog"和"walker"组成。
提示：

0 <= len(words) <= 200
1 <= len(words[i]) <= 100

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/longest-word-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。