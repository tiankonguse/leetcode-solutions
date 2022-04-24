# 1158. 市场分析 I

Table: Users

+----------------+---------+
| Column Name    | Type    |
+----------------+---------+
| user_id        | int     |
| join_date      | date    |
| favorite_brand | varchar |
+----------------+---------+
此表主键是 user_id。
表中描述了购物网站的用户信息，用户可以在此网站上进行商品买卖。
 

Table: Orders

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| order_id      | int     |
| order_date    | date    |
| item_id       | int     |
| buyer_id      | int     |
| seller_id     | int     |
+---------------+---------+
此表主键是 order_id。
外键是 item_id 和（buyer_id，seller_id）。
 

Table: Items

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| item_id       | int     |
| item_brand    | varchar |
+---------------+---------+
此表主键是 item_id。
 

请写出一条SQL语句以查询每个用户的注册日期和在 2019 年作为买家的订单总数。

以 任意顺序 返回结果表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/market-analysis-i
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。