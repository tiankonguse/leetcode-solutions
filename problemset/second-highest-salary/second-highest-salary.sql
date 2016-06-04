# Write your MySQL query statement below

 select t3.Salary as SecondHighestSalary from (select min(t2.Salary) as Salary, count(*) as Num, 0 as ok from ((select distinct t1.Salary as Salary from Employee t1 order by t1.Salary desc limit 2) t2)  union (SELECT null as Salary, 2 as Num, 1 as ok )) t3 where t3.Num = 2 order by ok limit 1;

