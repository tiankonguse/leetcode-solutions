# Please write a DELETE statement and DO NOT write a SELECT statement.
# Write your MySQL query statement below

delete FROM Person where id not in (select * from (select min(id) from Person group by email) as p1)