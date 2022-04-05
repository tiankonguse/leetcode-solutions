# 903. DI 序列的有效排列

给定一个长度为 n 的字符串 s ，其中 s[i] 是:

“D” 意味着减少，或者
“I” 意味着增加
有效排列 是对有 n + 1 个在 [0, n]  范围内的整数的一个排列 perm ，使得对所有的 i：

如果 s[i] == 'D'，那么 perm[i] > perm[i+1]，以及；
如果 s[i] == 'I'，那么 perm[i] < perm[i+1]。
返回 有效排列  perm的数量 。因为答案可能很大，所以请返回你的答案对 109 + 7 取余。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-permutations-for-di-sequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



