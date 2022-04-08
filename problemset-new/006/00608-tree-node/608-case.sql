# Write your MySQL query statement below
select
    id,
    case
        when id = (select R.id from tree R where R.p_id is null) then 'Root'
        when id in (select I.p_id from tree I) then 'Inner'
        else  "Leaf"
    end as Type
from
    tree