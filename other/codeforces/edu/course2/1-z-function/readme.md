Описание шага 步骤说明

Этот шаг посвящен базовым понятиям, определениям и формулировке задаче о поиске подстроки в строке. В видео обсуждаются такие термины как строка, подстрока, префикс, суффикс, вхождение. Сформулирована задача о поиске подстроки в строке. Обсуждаются два различных подхода к решению этой задачи — препроцессинг образца и препроцессинг текста.
这一步主要介绍在字符串中查找子串问题的基本概念、定义和表述。该视频讨论了字符串、子字符串、前缀、后缀、出现等术语。公式化了在字符串中查找子字符串的问题。讨论了解决此问题的两种不同方法 - 样本预处理和文本预处理。

https://media.codeforces.com/view/71933f8e4c93f9615d4958c7ddb4144500fb5bee3ff291ce1ddfcbd19666d90da6d322ec9fa72d2eb229431f46d80f45/Edu_Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F.pdf


定义：字符串，子字符串

字符串是有限（可能为空）的符号序列。字符串 s 的长度表示为 |s|。我们将符号从 0 到 |s|-1 进行编号。
示例字符串：s=“010101”，s=“abacaba”，s=[31,34,41]（符号—整数），s=“”。
子串 — 字符串中连续的字符序列。例如，字符串“apple”的所有子串包括：“apple”、“appl”、“pple”、“app”、“ppl”、“ple”、“ap”、“pp”、“pl”、“le”、“a”、“p”、“l”、“e”、“”。
定义子串 s[i … j]，它从 i 开始，到 j 结束。它的长度等于 j-i+1。


定义：出现次数、前缀、后缀

字符串 p 在字符串 t 中的匹配将被定义为一对索引 (i, j)，使得 p = t[i … j]。例如，在字符串 t="ababaaba" 中，字符串 p="aba" 共出现 3 次。
字符串 s 的前缀是指形式为 s[0 … i] 的子字符串。字符串 |s|+1 个前缀（空前缀和本身也计算在内）。例如，如果 s="abс"，那么前缀有 — "", "a", "ab", "abс"。
字符串 s 的后缀是指从 s[j … |s|-1] 开始的子字符串。字符串 s 总共有 |s|+1 个后缀（空后缀和整个字符串本身也包括在内）。例如，如果 s=“abс”，那么后缀分别是“”、“с”、“bc”、“abс”。


在字符串中查找子字符串（精确查找问题）

给定字符串 t（文本）和字符串 p（模式）。找到字符串 p 在字符串 t 中的所有出现。
例：t="abacababa"，p="aba"。答案包含 3 个匹配：
● abacababa: (0, 2)
● abacababa: (4, 6)
● abacababa: (6, 8)

如果 n=|t| 且 m=|p|，则朴素算法需要 O(nm) 时间。

在字符串中查找子字符串：朴素算法，两层循环

有两大主要方法：
● 模式预处理 (z-函数, 前缀函数)
● 文本预处理（后缀树，数组，自动机）


Z-函数: 定义

对于给定的字符串 s=s0s1 ...sn-1，其 z-函数是一个长度为 n 的数组 z，下标从 0 到 n-1，其中 z[i] 是字符串 s 和其后缀 s[i … n-1] 的最长公共前缀的长度。
对于 i=0 通常 z[0] = 0（有时方便认为 z[0] = n）。

例. 设 s="abacaba"

● z[0] = 0 — 按定义
● z[1] = 0 — 寻找最长公共子串的长度
abacaba 的前缀和 bacaba 的前缀
● z[2] = 1 — 寻找 abacaba 和 acaba 的最长公共前缀长度
● z[3] = 0 — 寻找 abacaba 和 caba 的最长公共前缀长度
● z[4] = 3 — 寻找 abacaba 和 aba 的最长公共前缀长度 
● z[5] = 0 — 寻找 abacaba 和 ba 的最长公共前缀长度 
● z[6] = 1 — 寻找 abacaba 和 a 的最长公共前缀长度 


Z-函数：例子

对于给定的字符串 s=ss...s，其 z-函数是一个长度为 n 的数组 z，从 0 到 n-1 索引，其中 z[i]表示整个字符串 s 与其子串 s[i…n-1]的最长公共前缀的长度。对于 i=0，通常 z[0] = 0（有时方便假设 z[0] = n）。

示例
s=「abacaba」，z=[0, 0, 1, 0, 3, 0, 1]
s=「aaaaaaaa」，z=[0, 7, 6, 5, 4, 3, 2, 1]
s=「abababab」，z=[0, 0, 6, 0, 4, 0, 2, 0]

Z-函数：练习
2 对于给定的字符串 s=ss...s，其 z-函数是一个长度为 n 的数组 z，从 0 到 n-1 索引，其中 z[i]表示整个字符串 s 与其子串 s[i…n-1]的最长公共前缀的长度。对于 i=0，通常 z[0] = 0（有时方便假设 z[0] = n）。

练习
查找字符串 s=「abaababa」的 Z-函数
找到字符串 s=「baababaab」的 Z-函数。

练习（答案）
s=「abaababa」，z=[0, 0, 1, 3, 0, 3, 0, 1]
s=「baababaab」，z=[0, 0, 0, 2, 0, 4, 0, 0, 1]

Z-函数：朴素算法
设计并实现一个简单的（平方的）算法来寻找字符串的 z-函数。


```python
for i = 1..n-1:
    while z[i] + i < n && s[z[i] + i] == s[z[i]]:
        z[i]++
```

Z-函数：用于搜索子串

假设我们能够有效地找到 z-函数。那么，关于在字符串中查找子串的问题也可以有效地解决。

给定文本 t 和样本 p。需要找到样本 p 在文本 t 中的所有出现。

构建新字符串 s 如下：s := p + ‘$’ + t，其中‘$’是一个既不在 t 也不在 p 中的符号。
找到字符串 s 的 z-函数。

如果 z[i]=|p|，则长度为 |p| 的子串从 i 开始与 s 的前 |p| 个字符相匹配，即等于 p。因此，存在 p 在 t 中的位置 i-|p|-1。反之亦然。


1. 构建 s := p + ‘$’ + t 
2. 找到字符串 s 的 z-函数 
3. 当且仅当 t 中存在以 i-|p|-1 为起始位置的 p 的子串时，z[i] = |p|

Z-算法

我们将从 i=1 开始，从左到右计算 z[i]的值。
我们将维护两个索引 l 和 r，使得 s[l .. r] 是字符串 s 的前缀，且 r 的值最大。

特别是，这意味着 s[l]=s[0]，s[l+1]=s[1]，…，s[i]=s[i-l]，…，s[r]=s[r-l]。
如果 i ≤ r，则让 i’=i-l，观察 z[i’] — 这个值将有助于找到 z[i]。

根据定义，z[i’]正确：s[0]=s[i’]，s[1]=s[i’+1]，…，s[z[i’]-1]=s[i’+z[i’]-1]，但记住，s[i’]=s[i]，s[i’+1]=s[i+1]，…，s[r-l]=s[r]。因此，s[0]=s[i]，s[1]=s[i+1]，…，以此类推，总共 min(z[i’]，r-i+1)次。
即 z[i] 部分已计算（z[i] ≥ min(z[i’], r-i+1)）。


Z-算法：情况 1.1
假设 i ≤ r，即 i 属于 [l, r]。那么 s[i] = s[i-l]，s[i+1] = s[i-l+1]，…，s[r] = s[r-l]。设 i' = i-l
— 在某种意义上是反映字符串已处理部分中的符号 i。


那么如果 z[i’]的值使得右边界匹配 i’+z[i’]-1 严格小于 r-l，那么从字符 i 开始也有完全相同的匹配，但没有更长的匹配。
根据定义，s[z[i’]] 和 s[i’ + z[i’]] 的符号不同（否则可以增加 z[i’]），但由于 s[i’ + z[i’]] = s[i + z[i’]]，因此 s[z[i’]] 和 s[i + z[i’]] 也不同。因此，z[i] 的值恰好等于 z[i’]。

例如，在图中 z[i’]=2。确实，所有红色弧线表示相同的子串，s[2] ≠ s[4]（否则 z[i’] 将是 3）。然而，由于 s[4]=s[10]，因此 s[2]≠s[10]。因此，z[8]=z[2]=2。


Z-算法：情况 1.2
假设 i ≤ r，即 i 属于 [l, r]。那么 s[i] = s[i-l]，s[i+1] = s[i-l+1]，…，s[r] = s[r-l]。设 i' = i-l
— 在某种意义上是反映字符串已处理部分中的符号 i。



如果 z[i’]的值使得右边界匹配 i’+z[i’]-1 ≥ r-l，那么从 z[i’]开始的整个匹配都不能使用，只能使用落入长度为 r-l+1 的前缀部分（蓝色部分）。换句话说，我们只能确保 z[i] ≥ r-l-i’+1 = r-l-(i-l)+1 = r-i+1。
因此，我们将 z[i] := r - l + 1，然后尝试以最简单的方式增加（直到正确值）。


Z-算法：情况 2

假设 i > r，那么之前计算出的 z 值不能使用。
在这种情况下，我们将从 0 开始以最简单的方式增加 z[i]（直到可以进行为止）。


Z-算法
我们将从 i=1 开始，从左到右计算 z[i]的值。
我们将维护两个索引 l 和 r，使得 s[l .. r] 是字符串 s 的前缀，且 r 的值最大。

特别是，这意味着 s[l]=s[0]，s[l+1]=s[1]，…，s[i]=s[i-l]，…，s[r]=s[r-l]。
如果 i ≤ r，那么看看 z[i-l] —这个值将有助于找到 z[i]。
    ○ 确实，长度为 r-i+1 的子串，分别从 i 和 i-l 开始，是相等的。
    ○ 如果 z[i-l] < r-i+1，那么 z[i] = z[i-l]。在这种情况下，z[i] 的值已经计算出来了。
    ○ 如果 z[i-l] ≥ r-i+1，那么 z[i] 确实大于或等于 r-i+1，但确切值未知。我们将以最简单的方式增加 z[i]，直到得到确切值。
如果 i>r，则没有关于 z[i] 的额外信息，我们将以最简单的方式计算 z[i]。
注意，长度为 s[i ... i + z[i] - 1] 的子串与前缀相同，如果需要（即如果 r < i + z[i] - 1），则重新计算 l 和 r。


Z-算法


```python
n = |s|, l = 0, r = 0
for i := 1 .. n - 1:
    if r >= i: # // 我们能否使用 [l,r]-块？
            if z[i - l] < r - i + 1: # //  z[i - l]的值是否短于右侧端点
                z[i] = z[i - l]
        else:
            z[i] = r - i + 1 # // 与右端匹配或更远
            while z[i] + i < n && s[z[i]] == s[z[i] + i]:
                z[i]++
    else:
        while z[i] + i < n && s[z[i]] == s[z[i] + i]:
            z[i]++
    if r < i + z[i] - 1: # //  重新计算 [l,r]? 维持 r->max
        l = i
        r = i + z[i] - 1
```

Z-算法：紧凑实现


```python
l = r = 0
for i = 1..n-1:
    if r >= i:
        z[i] = min(z[i - l], r - i + 1)
    while z[i] + i < n && s[z[i]] == s[z[i] + i]:
        z[i]++
    if i + z[i] - 1 > r:
        l = i, r = i + z[i] - 1
```

因为它每次在 while 循环中增加 z[i]时，索引 r 也会向右移动。它不可能移动超过 n 次。
可以缩短实现，如果将右边界设置为“非包含”，即使用[l, r)范式。


Z-函数：用于查找子串

在字符串中搜索子串
给定文本 t 和样本 p。需要找到样本 p 在文本 t 中的所有出现。


1. 构建 s := p + ‘$’ + t 
2. 找到字符串 s 的 z-函数 
3. 当且仅当 t 中存在以 i-|p|-1 为起始位置的 p 的子串时，z[i] = |p|



任务：给定两个字符串 s 和 t。需要检查 t 是否是 s 的循环移位。例如，对于字符串 abcd，其循环移位有：abcd, bcda, cdab 和 dabc。
解決方案：將字串 s 連續寫兩次。在得到的字串中找到 t 作為子字串。



Z-函数：行最大边界


行边界是指每个这样的行独有的前缀，同时它也是其后缀。独有的前缀（后缀）是指不同于行本身的前缀（后缀）。
例如，字符串 s=“abacaba”的边界是三个字符串：“”， “a”和“aba”。

任务：给定字符串 s。找出它的最长子串。例如，对于 s=「abacaba」，需要返回「aba」。
解決方案：要使用 z-函數找到最大的邊界，只需找到最小的 i，使得 i+z[i]=|s|。那麼，對應的 z[i] 就是字串 s 的最長邊界。


Z-函数：不同子字符串的数量为 O(n^2)

给定字符串 s，输出其中不同非空子字符串的数量。
例如，如果 s=abaaba，那么它的所有不同子串是 a、aa、aab、aaba、ab、aba、abaa、abaab、abaaba、b、ba、baa、baab、baaba。总共有 14 个。


从空字符串 t 开始，我们将从右到左“构建”字符串 s（每次将 s 的下一个字符添加到 t 的左侧：t = s[i] + t），直到达到完整的字符串 t=s。
在过程中将保持响应——当前字符串 t 的不同子字符串的数量。


每次都会添加“新的”行前缀 t。也就是说，那些之前未添加的前缀。也就是说，那些在 t 中未出现的前缀。
添加了这样的前缀 t，其长度超过了在右侧出现的最长前缀。
子任务。在字符串 t 中找到至少出现一次的最长前缀的长度。

解決方案。我們將找到字符串 t 的 z-函數，那麼其中最大值就是所求的最長前缀的長度，該前綴在 t 中作為非前綴出現。然後每次將 |t|-max{z(t)} 加到答案上。


给定字符串 s，输出其中不同非空子字符串的数量。


算法解决方案：
t = “”
对于 i 从 n-1 到 0
    ○ t = s[i] + t 
    ○ 将 i+1-max{z(t)}的响应增加，因为|t|=i+1

总共 O(n) 步，每步执行线性时间。总共，算法的总运行时间为 O(n^2)。


Z-函数：字符串周期


字符串 s 的周期长度定义为这样一个最小的数 k，即字符串 s 可以表示为长度为 k 的前缀的多个副本的连接。例如，对于字符串 s=abcabc，周期长度等于 3，对于字符串 s=aaaaa，周期长度等于 1，而对于字符串 s=abcab，周期长度等于 5。

显然，k 是字符串长度的约数。
找到给定字符串的周期长度，线性时间。



算法。找到字符串 s 的 z-函数。然后找到最小的正整数 i，使得 i+z[i]=|s|，并且 |s| 能被 i 整除——这是字符串的周期长度。如果不存在这样的 i，则周期长度等于 |s|。


充足性。如果 i 满足 i+z[i]=|s|，并且同时|s|能被 i 整除，那么我们将证明对于任何 j<|s|-i，都有 s[j] = s[j + i]。实际上，这两个字符在长度为 z[i]的对应前缀和长度相等的子串中是相等的，该子串从 i 开始。
如果对于任何 j < |s|-i，有 s[j] = s[j + i]（且 i 是 |s| 的除数），那么显然，该字符串以 i 为周期是周期的。


必要性。设 i 为字符串周期的长度，则长度为|s|-i 的前缀等于从 i 开始的相同长度的子串。因此，z[i] = |s|-i。此外，显然 i 是|s|的约数。



Z-函数：单错误搜索



给定文本 t 和样本 p。我们将一个包含一个错误的错误匹配称为索引对 (l, r)，其中 p[i]=t[i+l] 对于所有 i 从 0 到 |p|-1 成立，除了恰好一个情况 p[i]≠t[i+l]。

设 n=|t|，m=|p|。实际上，对于从 0 到 n-m 的每个 l，需要检查 l 是否是不精确匹配的起始点。为此，我们需要找到两个量：
整数 a — 最长公共前后缀的长度（如图所示，a=6）
整数 b — 最长公共后缀的长度（如图所示 b=3）。
请注意，当且仅当 a+b=m-1 时，l 是一个包含一个错误的近似匹配的开始。


找到 a 更简单。构建新的字符串 s = p + ‘$’ + t，计算它的 z-函数（如同在精确匹配任务中）。那么 a = z[m + 1 + l]。

为了找到 b，我们将构建 p'=rev(p)，t'=rev(t)（其中 rev(x)表示翻转字符串 x）和 s'=p'+$+t'。计算 s'的 z-函数 z'。那么所求的值 b 等于 z'[n-l+1]，因为(m+1)+(n-1)-(l+m-1)=n-l+1。



