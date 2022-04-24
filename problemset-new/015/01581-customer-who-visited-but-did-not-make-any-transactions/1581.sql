select C.customer_id customer_id, count(*) count_no_trans  
from Visits C
where C.visit_id not in (select visit_id from Transactions)
group by C.customer_id