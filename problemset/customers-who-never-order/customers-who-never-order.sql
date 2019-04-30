# Write your MySQL query statement below
select t1.Name as Name from Customers t1 where t1.Id not in (select t2.CustomerId as Id from Orders t2)
