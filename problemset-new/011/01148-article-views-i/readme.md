# 1148. 文章浏览 I

Views 表：

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| article_id    | int     |
| author_id     | int     |
| viewer_id     | int     |
| view_date     | date    |
+---------------+---------+
此表无主键，因此可能会存在重复行。
此表的每一行都表示某人在某天浏览了某位作者的某篇文章。
请注意，同一人的 author_id 和 viewer_id 是相同的。
 

请编写一条 SQL 查询以找出所有浏览过自己文章的作者，结果按照 id 升序排列。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/article-views-i
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。