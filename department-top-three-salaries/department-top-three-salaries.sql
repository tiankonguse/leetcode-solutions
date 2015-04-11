# Write your MySQL query statement below



select t2.Name as Department, t1.Name as Employee, t1.Salary as Salary from Department t1, Employee t2 where t1.DepartmentId = t2.DepartmentId and (t1.Id in (select top 3 t3.Id as Id from  Department t3 where t3.DepartmentId = t1.DepartmentId order by t3.Salary desc )) order by t2.Id, t1.Salary desc


# Write your MySQL query statement below





select t6.Department as Department, t6.Employee as Employee, t6.Salary as Salary 
from (
    select t5.Id as Id,t4.Id as DepartmentId, t4.Name as Department, t5.Name as Employee, t5.Salary as Salary 
    from Department t4, Employee t5 
    where t4.Id = t5.DepartmentId
    ) t6, (
        select t7.DepartmentId as DepartmentId,t7.Salary as Salary 
        from (
            select t1.DepartmentId as DepartmentId, t1.Salary as Salary 
            from (
                select min(Id) as Id, DepartmentId,Salary 
                from Employee 
                group by DepartmentId,Salary
            ) t1 , (
                select min(Id) as Id, DepartmentId,Salary 
                from Employee 
                group by DepartmentId,Salary
            ) t2 
            where t1.DepartmentId = t2.DepartmentId and t1.Salary <= t2.Salary 
            GROUP BY t1.Id 
            HAVING count(*) <= 3
        ) t7 
        group by t7.DepartmentId,t7.Salary
    ) t3 
where  t6.DepartmentId = t3.DepartmentId and t6.Salary >= t3.Salary 
order by t6.DepartmentId, t6.Salary desc;



# Write your MySQL query statement below


select distinct t6.Department as Department, t6.Employee as Employee, t6.Salary as Salary from (
select t5.Id as Id,t4.Id as DepartmentId, t4.Name as Department, t5.Name as Employee, t5.Salary as Salary from Department t4, Employee t5 where t4.Id = t5.DepartmentId) t6, (select t7.DepartmentId as DepartmentId,t7.Salary as Salary from (select t1.DepartmentId as DepartmentId, t1.Salary as Salary from (select min(Id) as Id, DepartmentId,Salary from Employee group by DepartmentId,Salary) t1 , (select min(Id) as Id, DepartmentId,Salary from Employee group by DepartmentId,Salary) t2 where t1.DepartmentId = t2.DepartmentId and t1.Salary <= t2.Salary GROUP BY t1.Id HAVING count(*) <= 3) t7 group by t7.DepartmentId,t7.Salary) t3 where  t6.DepartmentId = t3.DepartmentId and t6.Salary >= t3.Salary order by t6.DepartmentId, t6.Salary desc;
