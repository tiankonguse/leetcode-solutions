## leetcode 1178 - Number of Valid Words for Each Puzzle

题意：给一些 word 和 一些 puzzle。
当 puzzle 的第一个字母在 word 里面且 word 里所有字母都在 puzzle 里，则称 word 属于 puzzle.
问对于每个 puzzle，有多少个 word 属于它。


例如：puzzle 是 `aboveyz`， `aaaa` 是 word。
`aboveyz` 的第一个字母 `a` 在`aaa`中可以找到。
而`aaa`的所有单词都可以在`aboveyz`中找到。
所以`aaa`属于`aboveyz`。


思路：对于每个单词，是否属于一个 puzzle 只有判断了才知道。
所以这里可以进行暴力计算。


但是，默认是`O(n*m*len)`的复杂度，会超时。
我们可以通过预处理，来提高计算速度。

第一步是过滤无效的 word。因为 puzzle 长度是 7，那超过 7 的 word 都是无效的。
第二步是位压缩。默认判断是否属于，需要使用集合运算。而通过 位压缩，一次位判断即可得到结果。

综合这两个优化，这道题就可以过了。

——————————————

PS：这个代码在即将超时的边缘，如果自己使用其他语言或者c++实现的话，需要注意一下优化，尽量使用基础的数组不要使用对象。
另外，看到有人不枚举word，而是枚举 puzzle 的所有组合。
由于 puzzle 只有7位，所有组合也就 `2^7=128`，比 word 的数量少两个数量级，所以枚举 puzzle 更快，大家可以试试。


