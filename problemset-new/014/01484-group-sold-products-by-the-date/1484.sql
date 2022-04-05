# Write your MySQL query statement below

select 
    sell_date,
    count(DISTINCT product) num_sold, 
    group_concat(DISTINCT product ORDER BY product ASC SEPARATOR ',') products 
from Activities 
group by sell_date
ORDER BY sell_date;