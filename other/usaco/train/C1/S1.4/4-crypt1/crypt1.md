# Prime Cryptarithm 素数密码术

(This poorly named task has nothing to do with prime numbers or even, really, prime digits. Sorry 'bout that.)
（这个命名不佳的任务与素数无关，甚至与素数无关。抱歉。）

A cryptarithm is usually presented as a pencil-and-paper task in which the solver is required to substitute a digit for each of the asterisks (or, often, letters) in the manual evaluation of an arithmetic term or expression so that the consistent application of the digits results in a proper expression.
密码算法通常以纸笔任务的形式呈现，其中求解器需要在算术术语或表达式的手动计算中用数字替换每个星号（或者通常是字母），以便一致的应用数字的结果是正确的表达式。
A classic example is this cryptarithm, shown with its unique solution:
一个典型的例子是这个密码，以其独特的解决方案显示：

```
    SEND            9567       S->9  E->5  N->6  D->7
  + MORE          + 1085       M->1  O->0  R->8
  -------        -------
   MONEY           10652       Y->2

    发送 9567 S->9 E->5 N->6 D->7
  + 更多 + 1085 M->1 O->0 R->8
  -------        -------
   金钱 10652 Y->2
```

The following cryptarithm is a multiplication problem that can be solved by substituting digits from a specified set of N digits into the positions marked with *.
下面的密码是一个乘法问题，可以通过将指定的 N 位数字中的数字替换到标有 * 的位置来解决。
Since the asterisks are generic, any digit from the input set can be used for any of the asterisks; any digit may be duplicated as many times as desired.
由于星号是通用的，因此输入集中的任何数字都可以用于任何星号；任何数字都可以根据需要重复多次。

Consider using the set {2,3,5,7} for the cryptarithm below:
考虑使用集合 {2,3,5,7} 作为下面的密码：

      * * *
   x    * *
    -------
      * * *         <-- partial product 1 -- MUST BE 3 DIGITS LONG
    * * *           <-- partial product 2 -- MUST BE 3 DIGITS LONG
    -------
    * * * *

      * * *
   X    * *
    -------
      * * * <-- 部分积 1 -- 必须是 3 位长
    * * * <-- 部分积 2 -- 必须是 3 位长
    -------
    * * * *
Digits can appear only in places marked by `*'. Of course, leading zeroes are not allowed.
数字只能出现在标有“*”的位置。当然，不允许有前导零。
The partial products must be three digits long, even though the general case (see below) might have four digit partial products.
部分积的长度必须为三位数，即使一般情况（见下文）可能有四位数的部分积。

********** Note About Cryptarithm's Multiplication ************
********** 关于 Cryptarithm 乘法的注意事项 ************
In USA, children are taught to perform multidigit multiplication as described here. Consider multiplying a three digit number whose digits are 'a', 'b', and 'c' by a two digit number whose digits are 'd' and 'e':
在美国，孩子们被教导如何执行多位数乘法，如此处所述。考虑将数字为“a”、“b”和“c”的三位数乘以数字为“d”和“e”的两位数字：

[Note that this diagram shows far more digits in its results than
the required diagram above which has three digit partial products.]
[请注意，该图在其结果中显示的位数远多于上面所需的具有三位数部分乘积的图。]
          a b c     <-- number 'abc'
        x   d e     <-- number 'de'; the 'x' means 'multiply'
     -----------
p1      * * * *     <-- product of e * abc; first star might be 0 (absent)
p2    * * * *       <-- product of d * abc; first star might be 0 (absent)
     -----------
      * * * * *     <-- sum of p1 and p2 (e*abc + 10*d*abc) == de*abc
 a b c <-- 数字 'abc' x d e <-- 数字 'de'; 'x' 表示 '乘' ---------- p1 * * * * <-- e * abc 的乘积；第一个星可能是 0（不存在） p2 * * * * <-- d * abc 的乘积；第一个星可能是 0（不存在） ----------- * * * * * <-- p1 和 p2 之和 (e*abc + 10*d*abc) == de*abc
Note that the 'partial products' are as taught in USA schools. The first partial product is the product of the final digit of the second number and the top number. The second partial product is the product of the first digit of the second number and the top number.
请注意，“部分乘积”是美国学校所教授的。第一个部分乘积是第二个数字的最后一位数字与顶部数字的乘积。第二部分积是第二个数字的第一位数字与顶部数字的乘积。

Write a program that will find all solutions to the first cryptarithm above (with three digit partial-products) for any subset of supplied non-zero single-digits. Note that the multiplicands, partial products, and answers must all conform to the cryptarithm's framework.
编写一个程序，为所提供的非零个位数的任何子集找到上述第一个密码算法（具有三位数部分积）的所有解决方案。请注意，被乘数、部分积和答案都必须符合密码算法的框架。

PROGRAM NAME: crypt1
程序名称：crypt1
INPUT FORMAT 输入格式
Line 1:  1号线：	N, the number of digits that will be used
N，将使用的位数
Line 2:  2号线：	N space separated non-zero digits with which to solve the cryptarithm
N 个空格分隔的非零数字，用于求解密码
SAMPLE INPUT (file crypt1.in)
示例输入（文件 crypt1.in）
5
2 3 4 6 8
OUTPUT FORMAT 输出格式
A single line with the total number of solutions. Here is the one and only solution for the sample input:
单行显示解决方案的总数。这是示例输入的唯一解决方案：

      2 2 2
    x   2 2
     ------
      4 4 4
    4 4 4
  ---------
    4 8 8 4

      2 2 2
x 2 2
     ------
      4 4 4
    4 4 4
  ---------
    4 8 8 4
SAMPLE OUTPUT (file crypt1.out)
示例输出（文件 crypt1.out）
1
OUTPUT DETAILS 输出详细信息
Here's why 222x22 works: 3 digits times 2 digits yields two (equal!) partial products, each of three digits (as required). The answer has four digits, as required. Each digit used {2, 4, 8} is in the supplied set {2, 3, 4, 6, 8}.
这就是 222x22 有效的原因：3 位数字乘以 2 位数字会产生两个（相等！）部分积，每个部分积都是三位数（根据需要）。根据要求，答案有四位数字。使用的每个数字 {2, 4, 8} 都在提供的集合 {2, 3, 4, 6, 8} 中。

Why 222x23 doesn't work:
为什么 222x23 不起作用：

      2 2 2   <-- OK:  three digits, all members of {2, 3, 4, 6, 8}
        2 3   <-- OK:  two digits, all members of {2, 3, 4, 6, 8}
     ------
      6 6 6   <-- OK:  <b>three</b> digits, all members of {2, 3, 4, 6, 8}
    4 4 4     <-- OK:  <b>three</b> digits, all members of {2, 3, 4, 6, 8}
  ---------
    5 1 0 6   <-- NOT OK: four digits (good), but 5, 1, and 0 are not in
                                                    {2, 3, 4, 6, 8}

      2 2 2 <-- OK：三位数，{2,3,4,6,8}的所有成员
        2 3 <-- OK: 两位数，{2, 3, 4, 6, 8} 的所有成员
     ------
      6 6 6 <-- 好的：<b>三位 位数字，{2, 3, 4, 6, 8} 的所有成员
    4 4 4 <-- OK：<b>三位数，{2, 3, 4, 6, 8} 的所有成员
  ---------
    5 1 0 6 <-- 不正常：四位数字（好），但 5、1 和 0 不在
                                                    {2, 3, 4, 6, 8}