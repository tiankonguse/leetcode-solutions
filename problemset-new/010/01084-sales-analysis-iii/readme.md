# 1084. 销售分析III

Table: Product

+--------------+---------+
| Column Name  | Type    |
+--------------+---------+
| product_id   | int     |
| product_name | varchar |
| unit_price   | int     |
+--------------+---------+
Product_id是该表的主键。
该表的每一行显示每个产品的名称和价格。
Table: Sales

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| seller_id   | int     |
| product_id  | int     |
| buyer_id    | int     |
| sale_date   | date    |
| quantity    | int     |
| price       | int     |
+------ ------+---------+
这个表没有主键，它可以有重复的行。
product_id 是 Product 表的外键。
该表的每一行包含关于一个销售的一些信息。
 

编写一个SQL查询，报告2019年春季才售出的产品。即仅在2019-01-01至2019-03-31（含）之间出售的商品。

以 任意顺序 返回结果表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sales-analysis-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。