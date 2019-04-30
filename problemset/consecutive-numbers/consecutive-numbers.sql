# Write your MySQL query statement below
select distinct t4.Num as Num  from Logs t4 ,(select t1.Id as Id, t1.Num as Num from Logs t1,Logs t2 where t1.Id = t2.Id - 1 and  t1.Num = t2.Num) t3 where t4.Id = t3.Id - 1 and t4.Num = t3.Num;
