# 1050. 合作过至少三次的演员和导演

SQL架构
ActorDirector 表：

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| actor_id    | int     |
| director_id | int     |
| timestamp   | int     |
+-------------+---------+
timestamp 是这张表的主键.
 

写一条SQL查询语句获取合作过至少三次的演员和导演的 id 对 (actor_id, director_id)