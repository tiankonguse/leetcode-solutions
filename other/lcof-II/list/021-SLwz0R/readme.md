# 剑指 Offer II 021. 删除链表的倒数第 n 个结点

给定一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

 

示例 1：

![](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)


输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]
 

提示：

链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 

进阶：能尝试使用一趟扫描实现吗？

 

注意：本题与主站 19 题相同： https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/SLwz0R
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。