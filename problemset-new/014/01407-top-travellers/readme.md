# 1407. 排名靠前的旅行者

表：Users

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| id            | int     |
| name          | varchar |
+---------------+---------+
id 是该表单主键。
name 是用户名字。
 

表：Rides

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| id            | int     |
| user_id       | int     |
| distance      | int     |
+---------------+---------+
id 是该表单主键。
user_id 是本次行程的用户的 id, 而该用户此次行程距离为 distance 。
 

写一段 SQL , 报告每个用户的旅行距离。

返回的结果表单，以 travelled_distance 降序排列 ，如果有两个或者更多的用户旅行了相同的距离, 那么再以 name 升序排列 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/top-travellers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。