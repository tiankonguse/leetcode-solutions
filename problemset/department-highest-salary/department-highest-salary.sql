
select t4.Name as DepartmentId, t3.Name as Employee, t3.Salary as Salary  from (select t1.DepartmentId as DepartmentId, max(t1.Salary) as Salary from Employee t1 group by t1.DepartmentId) t2, Employee t3, Department  t4 where t2.DepartmentId = t3.DepartmentId  and t2.Salary = t3.Salary  and t2.DepartmentId = t4.Id ;

