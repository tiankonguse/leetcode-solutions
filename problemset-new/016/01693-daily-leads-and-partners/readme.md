# 1693. 每天的领导和合伙人

表：DailySales

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| date_id     | date    |
| make_name   | varchar |
| lead_id     | int     |
| partner_id  | int     |
+-------------+---------+
该表没有主键。
该表包含日期、产品的名称，以及售给的领导和合伙人的编号。
名称只包含小写英文字母。
 

写一条 SQL 语句，使得对于每一个 date_id 和 make_name，返回不同的 lead_id 以及不同的 partner_id 的数量。

按 任意顺序 返回结果表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/daily-leads-and-partners
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。