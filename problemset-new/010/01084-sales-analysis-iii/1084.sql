select A.product_id product_id,A.product_name product_name 
from Product A 
where A.product_id in (select product_id from Sales where sale_date >= '2019-01-01' and sale_date <= '2019-03-31')
and A.product_id not in (select product_id from Sales where sale_date < '2019-01-01' or sale_date > '2019-03-31')