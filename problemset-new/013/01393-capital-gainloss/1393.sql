select A.stock_name stock_name, sum(A.price)  capital_gain_loss
from (select stock_name, if(`operation`="Buy",  -1 * price, 1 * price) price from Stocks) A
group by A.stock_name




select stock_name, sum(if(`operation`="Buy",  -1 * price, 1 * price)) capital_gain_loss
from Stocks 
group by stock_name