select U.user_id buyer_id, U.join_date join_date, ifnull(O.num, 0) orders_in_2019
from Users U left join (
    select buyer_id, count(*) num 
    from  Orders 
    where order_date >= "2019-01-01" and order_date <= "2019-12-31" 
    group by buyer_id) O 
on U.user_id = O.buyer_id
