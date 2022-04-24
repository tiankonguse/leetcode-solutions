select account,sum(amount) from Transactions group by account

select A.name name,B.balance balance
from Users A, (select account,sum(amount) balance from Transactions group by account) B 
where A.account = B.account and B.balance > 10000;