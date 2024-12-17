# Substring search 子串搜索

Well, we learned how to build a suffix array for a given string in 𝑂(𝑛log𝑛)
 time, let's learn how to use it.
好吧，我们学习了如何为给定字符串构建后缀数组 𝑂(𝑛log𝑛)
 有时间，我们来学习一下如何使用它。
The first task we will solve is the substring search task. Suppose we have a string 𝑠
 and need to answer the requests. Each request is a string 𝑝
. We need to answer whether the string 𝑝
 appears in the string 𝑠
 as a substring.
我们要解决的第一个任务是子串搜索任务。假设我们有一个字符串 𝑠
 并需要回答请求。每个请求都是一个字符串 𝑝
 。我们需要回答字符串是否 𝑝
 出现在字符串中 𝑠
 作为子串。

Let's notice that any substring is a prefix of some suffix. Let's look at the suffix array of the string 𝑠
. Let the length of string 𝑝
 be equal to |𝑝|
. If we cut off the first |𝑝|
 characters from each suffix, we get all substrings of length |𝑝|
 in sorted order. Now among them we need to find the string 𝑝
. This can be done using a binary search. The binary search run time will be 𝑂(|𝑝|log𝑛)
, because each string comparison works in 𝑂(|𝑝|)
 time. Try to program it yourself and solve the problem in practice section.
让我们注意到任何子字符串都是某个后缀的前缀。我们看一下字符串的后缀数组 𝑠
 。设字符串的长度 𝑝
 等于 |𝑝|
 。如果我们切断第一个 |𝑝|
 每个后缀的字符，我们得到所有长度的子串 |𝑝|
 按排序顺序。现在我们需要在其中找到字符串 𝑝
 。这可以使用二分搜索来完成。二分查找的运行时间为 𝑂(|𝑝|log𝑛)
 ，因为每个字符串比较都适用于 𝑂(|𝑝|)
 时间。尝试自己编程并解决实践部分的问题。