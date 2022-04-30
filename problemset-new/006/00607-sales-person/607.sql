select
  C.name
from
  SalesPerson C
where
  C.sales_id not in (
    select
      A.sales_id
    from
      Orders A,
      Company B
    where
      A.com_id = B.com_id
      and B.name = 'RED'
  )