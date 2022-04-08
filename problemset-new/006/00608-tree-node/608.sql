# Write your MySQL query statement below

select id, "Root" Type from tree where p_id is null
UNION 
select id, "Inner" Type from tree where id in (select p_id from tree where p_id is not null) and p_id is not null
UNION 
select id, "Leaf" Type from tree where id not in (select p_id from tree where p_id is not null) and p_id is not null