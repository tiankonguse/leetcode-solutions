# 1729. 求关注者的数量

表： Followers

+-------------+------+
| Column Name | Type |
+-------------+------+
| user_id     | int  |
| follower_id | int  |
+-------------+------+
(user_id, follower_id) 是这个表的主键。
该表包含一个关注关系中关注者和用户的编号，其中关注者关注用户。
 

写出 SQL 语句，对于每一个用户，返回该用户的关注者数量。

按 user_id 的顺序返回结果表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-followers-count
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。