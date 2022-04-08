# Write your MySQL query statement below

select product_id, "store1" store, store1 price from Products where store1 is not null
UNION
select product_id, "store2" store, store2 price from Products where store2 is not null
UNION
select product_id, "store3" store, store3 price from Products where store3 is not null