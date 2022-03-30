# Write your MySQL query statement below
select t1.Name as Employee  from Employee t1, Employee t2 where t1.ManagerId  = t2.Id and t1.Salary  > t2.Salary;
